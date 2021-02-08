//
// Copyright © 2020 Vladimir Mashir
//

#include <Level.h>
#include <nlohmann/json.hpp>
#include <fstream>

int Object::GetPropertyInt(std::string &input)
{
    return stoi(properties[input]);
}

float Object::GetPropertyFloat(std::string &input)
{
    return stof(properties[input]);
}

std::string Object::GetPropertyString(const std::string &input)
{
    return properties[name];
}

b2Body* Level::GetPlayerBody()
{
    return playerBody;
}

bool Level::LoadFromFile(const std::string &filename)
{
    std::fstream map(filename);

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

    std::vector<sf::Rect < int>>
    subRects;

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

            /* create a new layer */
            Layer thisLayer;

            /* set opacity */
            if (layer["opacity"].get<int>() != 1) {
                thisLayer.opacity = 255 * layer["opacity"].get<int>();
            } else {
                thisLayer.opacity = 255;
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
                        sprite.setPosition( x * float(tileWidth), y * float(tileHeight));
                        sprite.setColor(sf::Color(255, 255, 255, thisLayer.opacity));

                        thisLayer.tiles.push_back(sprite);
                    }

                    ++x;
                    if (x >= float(width)) {
                        x = 0;
                        ++y;
                        if (y >= float(height)) {
                            y = 0;
                        }
                    }
                    layers.push_back(thisLayer);
                }
            }
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

                Object thisObject;
                thisObject.name = objectName;
                thisObject.type = objectType;
                thisObject.sprite = sprite;

                sf::Rect<int> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;

                thisObject.rect = objectRect;

                if (object.contains("property")) {
//                            std::string propertyName  = prop->Attribute("name");
//                            std::string propertyValue = prop->Attribute("value");
//
//                            object.properties[propertyName] = propertyValue;
//
//                            prop = prop->NextSiblingElement("property");

                }
                objects.push_back(thisObject);
            }
        }
    }
    return true;
}

Object Level::GetObject(const std::string &name)
{
    for (const auto &el : objects) {
        if (el.name == name) {
            return el;
        }
    }
    return *objects.end();
}

std::vector<Object> Level::GetObjects(const std::string &name)
{
    std::vector<Object> vec;
    for (const auto &el : objects) {
        if (el.name == name) {
            vec.push_back(el);
        }
    }
    return vec;
}

sf::Vector2i Level::GetTileSize() const
{
    return sf::Vector2i(tileWidth, tileHeight);
}

void Level::Draw(sf::RenderWindow &window)
{
    for (const auto &layer : layers) {
        for (const auto &tile : layer.tiles) {
            window.draw(tile);
        }
    }
    for(const auto & el : coin) {
        window.draw(el.sprite);
    }

    for(const auto & el : coin) {
        window.draw(el.sprite);
    }
}


void Level::update(sf::View &view, sf::Vector2i &screenSize)
{
    for(b2ContactEdge* ce = playerBody->GetContactList(); ce; ce = ce->next) {
        b2Contact* c = ce->contact;

        for(int i = 0; i < coinBody.size(); i++)
            if(c->GetFixtureA() == coinBody[i]->GetFixtureList()) {
                coinBody[i]->DestroyFixture(coinBody[i]->GetFixtureList());
                coin.erase(coin.begin() + i);
                coinBody.erase(coinBody.begin() + i);
            }

        for(int i = 0; i < enemyBody.size(); i++) {
            if (c->GetFixtureA() == enemyBody[i]->GetFixtureList()) {
                if (playerBody->GetPosition().y < enemyBody[i]->GetPosition().y) {
                    playerBody->SetLinearVelocity(b2Vec2(0.0f, -10.0f));

                    enemyBody[i]->DestroyFixture(enemyBody[i]->GetFixtureList());
                    enemy.erase(enemy.begin() + i);
                    enemyBody.erase(enemyBody.begin() + i);
                } else {
                    int tmp = (playerBody->GetPosition().x < enemyBody[i]->GetPosition().x)
                              ? -1 : 1;
                    playerBody->SetLinearVelocity(b2Vec2(10.0f * float(tmp), 0.0f));
                }
            }
        }
    }

    for(const auto &el : enemyBody)
    {
        if(el->GetLinearVelocity() == b2Vec2_zero)
        {
            int tmp = (rand() % 2 == 1) ? 1 : -1;
            el->SetLinearVelocity(b2Vec2(5.0f * float(tmp), 0.0f));
        }
    }

    b2Vec2 pos = playerBody->GetPosition();
    view.setCenter(pos.x + float(screenSize.x) / 4, pos.y + float(screenSize.y) / 4);

    player.sprite.setPosition(pos.x, pos.y);

    for(int i = 0; i < coin.size(); i++) {
        coin[i].sprite.setPosition(coinBody[i]->GetPosition().x, coinBody[i]->GetPosition().y);
    }

    for(int i = 0; i < enemy.size(); i++) {
        enemy[i].sprite.setPosition(enemyBody[i]->GetPosition().x, enemyBody[i]->GetPosition().y);
    }
}

void Level::initObjects(Level &lvl)
{
    sf::Vector2i tileSize = lvl.GetTileSize();
    b2World world(gravity);

    std::vector<Object> block = lvl.GetObjects("solid");
    for(const auto &el : block)
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(float(el.rect.left) + float(tileSize.x) / 2 * (float(el.rect.width) / float(tileSize.x - 1)),
                             float(el.rect.top) + float(tileSize.y) / 2 * (float(el.rect.height / float(tileSize.y - 1))));
        b2Body* body = world.CreateBody(&bodyDef);
        b2PolygonShape shape;
        shape.SetAsBox(float(el.rect.width) / 2, float(el.rect.height) / 2);
        body->CreateFixture(&shape,1.0f);
    }

    coin = lvl.GetObjects("coin");
    for(const auto &el : coin)
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(float(el.rect.left) + float(tileSize.x) / 2 * (float(el.rect.width) / float(tileSize.x - 1)),
                             float(el.rect.top) + float(tileSize.y) / 2 * (float(el.rect.height / float(tileSize.y - 1))));
        bodyDef.fixedRotation = true;
        b2Body* body = world.CreateBody(&bodyDef);
        b2PolygonShape shape;
        shape.SetAsBox(float(el.rect.width) / 2, float(el.rect.height) / 2);
        body->CreateFixture(&shape,1.0f);
        coinBody.push_back(body);
    }

    enemy = lvl.GetObjects("enemy");
    for(const auto &el: enemy)
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(float(el.rect.left) + float(tileSize.x) / 2 * (float(el.rect.width) / float(tileSize.x - 1)),
                             float(el.rect.top)  + float(tileSize.y) / 2 * (float(el.rect.height / float(tileSize.y - 1))));
        bodyDef.fixedRotation = true;
        b2Body* body = world.CreateBody(&bodyDef);
        b2PolygonShape shape;
        shape.SetAsBox(float(el.rect.width) / 2, float(el.rect.height) / 2);
        body->CreateFixture(&shape,1.0f);
        enemyBody.push_back(body);
    }


    player = lvl.GetObject("player");
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(player.rect.left, player.rect.top);
    bodyDef.fixedRotation = true;
    playerBody = world.CreateBody(&bodyDef);
    b2PolygonShape shape; shape.SetAsBox(float(player.rect.width) / 2, float(player.rect.height) / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f; fixtureDef.friction = 0.3f;
    playerBody->CreateFixture(&fixtureDef);
}