//
// Copyright © 2020 Vladimir Mashir
//

#include <World.h>
#define TILE_DIV 32.0f

World::World()
{
    gravity.Set(1.0f, 0.0f);
    physicsWorld = new b2World(gravity);
}

Player& World::GetPlayer()
{
    return player;
}


const Object& World::GetObject(const std::string &name) const
{
    for (const auto &el : objects) {
        if (el.GetName() == name) { return el; }
    }
    return objects.back();
}

std::vector<std::unique_ptr<Object>> World::GetObjects(const std::string &name)
{
    std::vector<std::unique_ptr<Object>> vec;
    for (auto el = objects.begin(); el != objects.end(); el++) {
        if (el->GetName() == name) {
            vec.push_back(std::make_unique<Object>(*el));
        }
    }
    return vec;
}

const sf::Vector2i World::GetTileSize() const
{
    return sf::Vector2i(tileWidth, tileHeight);
}

bool World::LoadLevel(const std::string &filename)
{
    std::ifstream map(filename);

    if (!map.is_open()) {
        std::cout << "loading \"" << filename << "\" failed." << std::endl;
        return false;
    }

    // map parsing
    nlohmann::json jmap = nlohmann::json::parse(map);

    map.close();

    // take map and tileset's parameters
    width = jmap["width"].get<int>();      // map's width
    height = jmap["height"].get<int>();     // map's height
    tileWidth = jmap["tilewidth"].get<int>();  // tileset's width
    tileHeight = jmap["tileheight"].get<int>(); // tileset's height

    // take first's tileset's ID's
    for (const auto &el : jmap["tilesets"]) {
        firstTileIDs.emplace_back(std::make_pair(el["image"].get<std::string>(),
                                                 el["firstgid"].get<int>()));
    }

    sf::Image image;

    if (!image.loadFromFile(firstTileIDs[0].first)) {
        std::cout << "failed to load tile sheet." << std::endl;
        return false;
    }

    // map properties
    image.createMaskFromColor(sf::Color(109, 159, 185));

    // tileset's properties
    tileSetImage.loadFromImage(image);
    tileSetImage.setSmooth(false);

    int rows    = int(tileSetImage.getSize().y / tileHeight);
    int columns = int(tileSetImage.getSize().x / tileWidth);

    std::vector<sf::Rect<int>> subRects;

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            sf::Rect<int> rect;

            rect.top = y * tileHeight;
            rect.height = tileHeight;

            rect.left = x * tileWidth;
            rect.width = tileWidth;

            subRects.push_back(rect);
        }
    }

    /* layer processing */
    for (const auto &layer : jmap["layers"]) {
        if (layer["type"] == "tilelayer") {

            // create a new layer
            Layer thisLayer;

            // set opacity
            if (layer["opacity"].get<int>() != 1) {
                auto op = 255 * layer["opacity"].get<int>();
                thisLayer.SetOpacity(op);
            } else {
                auto op = 255;
                thisLayer.SetOpacity(op);
            }

            float x = 0;
            float y = 0;

            if (layer.contains("data")) {
                for (const auto &el : layer["data"]) {
                    int subRectToUse = el.get<int>() - firstTileIDs[0].second;

                    if (subRectToUse >= 0) {
                        sf::Sprite sprite;

                        sprite.setTexture(tileSetImage);
                        sprite.setTextureRect(subRects[subRectToUse]);
                        sprite.setPosition(x * float(tileWidth), y * float(tileHeight));
                        sprite.setColor(sf::Color(255, 255, 255, thisLayer.GetOpacity()));

                        thisLayer.SetSprite(sprite);
                    }

                    ++x;
                    if (x >= float(width)) {
                        x = 0;
                        ++y;
                        if (y >= float(height)) {
                            y = 0;
                        }
                    }
                }
            }
            layers.push_back(thisLayer);
        }

        if (layer["type"] == "objectgroup") {

            for (const auto &object : layer["objects"]) {

                std::string objectType;
                objectType = object["type"].get<std::string>();

                std::string objectName;
                objectName = object["name"].get<std::string>();

                auto x = object["x"].get<float>();
                auto y = object["y"].get<float>();

                sf::Sprite sprite;
                sprite.setTexture(tileSetImage);
                sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
                sprite.setPosition(x, y);

                width = object["width"].get<float>();
                height = object["height"].get<float>();

                if (object["name"].get<std::string>() == "playerStartPos") {
                    sf::Rect<float> objectRect;
                    objectRect.top  = y;
                    objectRect.left = x;
                    objectRect.height = height;
                    objectRect.width  = width;

                    player.SetRect(objectRect);
                    continue;
                }

                Object thisObject;
                thisObject.SetName(objectName);
                thisObject.SetType(objectType);
                thisObject.SetSprite(sprite);

                sf::Rect<float> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;

                thisObject.SetRect(objectRect);

                if (object.contains("property")) {
//                    std::string propertyName  = prop->Attribute("name");
//                    std::string propertyValue = prop->Attribute("value");
//
//                    object.properties[propertyName] = propertyValue;
//
//                    prop = prop->NextSiblingElement("property");

                }
                objects.push_back(thisObject);
            }
        }
    }
    return true;
}

void World::initObjects(World &lvl)
{
    sf::Vector2i tileSize = lvl.GetTileSize();

    //init static solid block's
    std::vector<std::unique_ptr<Object>> solid = lvl.GetObjects("solid");
    for(auto el = solid.begin(); el != solid.end(); el++) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(((*el)->GetRect().left + float(tileSize.x) / 2 * ((*el)->GetRect().width / tileSize.x - 1)) / TILE_DIV,
                             ((*el)->GetRect().top + float(tileSize.y) / 2 * ((*el)->GetRect().height / tileSize.y - 1)) / TILE_DIV);
        (*el)->SetBody(physicsWorld->CreateBody(&bodyDef));
        b2PolygonShape shape;
        shape.SetAsBox(float((*el)->GetRect().width) / 2 / TILE_DIV, float((*el)->GetRect().height) / 2 / TILE_DIV);
        (*el)->GetBody()->CreateFixture(&shape, 1.0f);
    }

    enemy = lvl.GetObjects("enemy");
    for(auto el = enemy.begin(); el != enemy.end(); el++) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(((*el)->GetRect().left + float(tileSize.x) / 2 * ((*el)->GetRect().width / float(tileSize.x - 1))) / TILE_DIV,
                             ((*el)->GetRect().top  + float(tileSize.y) / 2 * ((*el)->GetRect().height / float(tileSize.y - 1))) / TILE_DIV);
        bodyDef.fixedRotation = true;
        (*el)->SetBody(physicsWorld->CreateBody(&bodyDef));
        b2PolygonShape shape;
        shape.SetAsBox(float((*el)->GetRect().width) / 2 / TILE_DIV, float((*el)->GetRect().height) / 2 / TILE_DIV);
        (*el)->GetBody()->CreateFixture(&shape,1.0f);
    }

    b2BodyDef bodyDef;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(player.GetRect().left / TILE_DIV, player.GetRect().top / TILE_DIV);
    bodyDef.fixedRotation = true;
    player.SetBody(physicsWorld->CreateBody(&bodyDef));
    b2PolygonShape shape;
    shape.SetAsBox(float(player.GetRect().width) / 2 / TILE_DIV, float(player.GetRect().height) / 2 / TILE_DIV);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f; fixtureDef.friction = 0.3f;
    player.GetBody()->CreateFixture(&fixtureDef);
    physicsWorld->SetGravity(b2Vec2(0.0f, 10.0f));
}

void World::LevelUpdate(sf::View &view, const sf::Vector2i &screenSize)
{
    physicsWorld->Step(1.0f / 60.0f, 1, 1);

    for(b2ContactEdge* ce = player.GetBody()->GetContactList(); ce; ce = ce->next) {
        b2Contact* c = ce->contact;

         for(auto i = coin.begin(); i != coin.end(); i++) {
            if (c->GetFixtureA() == (*i)->GetBody()->GetFixtureList()) {
                (*i)->GetBody()->DestroyFixture((*i)->GetBody()->GetFixtureList());
                coin.erase(i);
                coin.erase(i);
            }
         }

        for(auto i = enemy.begin(); i != enemy.end(); i++) {
            if (c->GetFixtureA() == (*i)->GetBody()->GetFixtureList()) {
                if (player.GetBody()->GetPosition().y < (*i)->GetBody()->GetPosition().y) {
                    player.GetBody()->SetLinearVelocity(b2Vec2(0.0f, -10.0f));

                    (*i)->GetBody()->DestroyFixture((*i)->GetBody()->GetFixtureList());
                    enemy.erase(i);
                    i--;
                } else {
                    int tmp = (player.GetBody()->GetPosition().x < (*i)->GetBody()->GetPosition().x) ? -1 : 1;
                    player.GetBody()->SetLinearVelocity(b2Vec2(10.0f * float(tmp), 0.0f));
                }
            }
        }
    }

    for(auto el = enemy.begin(); el != enemy.end(); el++)
    {
        if((*el)->GetBody()->GetLinearVelocity() == b2Vec2_zero)
        {
            int tmp = (rand() % 2 == 1) ? 1 : -1;
            (*el)->GetBody()->SetLinearVelocity(b2Vec2(5.0f * float(tmp), 0.0f));
        }
    }
}

void World::Draw(sf::RenderWindow &window) const
{
    for (const auto &layer : layers) {
        for (const auto &tile : layer.GetTilesVector()) {
            window.draw(tile);
        }
    }
    for(auto el = enemy.begin(); el != enemy.end(); el++) {
        window.draw((*el)->GetSprite());
    }

    for(auto el = coin.begin(); el != coin.end(); el++) {
        window.draw((*el)->GetSprite());
    }
}
