//
// Copyright © 2020 Vladimir Mashir
//

#include <Level.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>
#include <cmath>
#define TILE_DIV 32.0f

Level::Level()
{
    gravity.Set(1.0f, 0.0f);
    world = new b2World(gravity);
}

Player& Level::GetPlayer()
{
    return player;
}

std::vector<sf::Sprite> Layer::GetTilesVector() const
{
    return tiles;
}

void Layer::SetOpacity(const int op)
{
    opacity = op;
}

void Layer::SetSprite(const sf::Sprite &inputSprite)
{
    tiles.push_back(inputSprite);
}

int Layer::GetOpacity() const
{
    return opacity;
}

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
    return properties.at(input);
}

const sf::Rect<int>& Object::GetRect() const
{
    return rect;
}

const std::string& Object::GetName() const
{
    return name;
}

const sf::Sprite& Object::GetSprite() const
{
    return sprite;
}

void Object::SetName(const std::string &inputName)
{
    name = inputName;
}

void Object::SetType(const std::string &inputType)
{
    type = inputType;
}

void Object::SetSprite(const sf::Sprite &inputSprite)
{
    sprite = inputSprite;
}

void Object::SetRect(const sf::Rect<int> &inputRect)
{
    rect = inputRect;
}

const Object& Level::GetObject(const std::string &name) const
{
    for (const auto &el : objects) {
        if (el.GetName() == name) { return el; }
    }
    return objects.back();
}

const std::vector<Object> Level::GetObjects(const std::string &name) const
{
    std::vector<Object> vec;
    for (const auto &el : objects) {
        if (el.GetName() == name) {
            vec.push_back(el);
        }
    }
    return vec;
}

const sf::Vector2i Level::GetTileSize() const
{
    return sf::Vector2i(tileWidth, tileHeight);
}

bool Level::LoadLevel(const std::string &filename)
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

    std::vector<sf::Rect < int>> subRects;

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
                    sf::Rect<int> objectRect;
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

                sf::Rect<int> objectRect;
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

void Level::initObjects(const Level &lvl)
{
    sf::Vector2i tileSize = lvl.GetTileSize();

    //init static solid block's
    std::vector<Object> solid = lvl.GetObjects("solid");
    for(const auto &el : solid) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set((float(el.GetRect().left) + float(tileSize.x) * (float(el.GetRect().width) / float(tileSize.x - 1))) / TILE_DIV,
                             (float(el.GetRect().top) + float(tileSize.y) / 2 * (float(el.GetRect().height / float(tileSize.y - 1)))) / TILE_DIV);
        b2Body* body = world->CreateBody(&bodyDef);
        b2PolygonShape shape;
        shape.SetAsBox(float(el.GetRect().width) / 2 / TILE_DIV, float(el.GetRect().height) / 2 / TILE_DIV);
        body->CreateFixture(&shape, 1.0f);
    }

    enemy = lvl.GetObjects("enemy");
    for(const auto &el: enemy) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set((float(el.GetRect().left) + float(tileSize.x) / 2 * (float(el.GetRect().width) / float(tileSize.x - 1))) / TILE_DIV,
                             (float(el.GetRect().top)  + float(tileSize.y) / 2 * (float(el.GetRect().height / float(tileSize.y - 1)))) / TILE_DIV);
        bodyDef.fixedRotation = true;
        b2Body* body = world->CreateBody(&bodyDef);
        b2PolygonShape shape;
        shape.SetAsBox(float(el.GetRect().width) / 2 / TILE_DIV, float(el.GetRect().height) / 2 / TILE_DIV);
        body->CreateFixture(&shape,1.0f);
        enemyBody.push_back(body);
    }

    b2BodyDef bodyDef;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(player.GetRect().left / TILE_DIV, player.GetRect().top / TILE_DIV);
    bodyDef.fixedRotation = true;
    player.playerBody = world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(float(player.GetRect().width) / 2 / TILE_DIV, float(player.GetRect().height) / 2 / TILE_DIV);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f; fixtureDef.friction = 0.3f;
    player.GetPlayerBody()->CreateFixture(&fixtureDef);
    world->SetGravity(b2Vec2(0.0f, 10.0f));
}

void Level::LevelUpdate(sf::View &view, const sf::Vector2i &screenSize)
{
    world->Step(1.0f / 60.0f, 1, 1);

    for(b2ContactEdge* ce = player.GetPlayerBody()->GetContactList(); ce; ce = ce->next) {
        b2Contact* c = ce->contact;

         for(int i = 0; i < coinBody.size(); i++) {
            if (c->GetFixtureA() == coinBody[i]->GetFixtureList()) {
                coinBody[i]->DestroyFixture(coinBody[i]->GetFixtureList());
                coin.erase(coin.begin() + i);
                coinBody.erase(coinBody.begin() + i);
            }
         }

        for(int i = 0; i < enemyBody.size(); i++) {
            if (c->GetFixtureA() == enemyBody[i]->GetFixtureList()) {
                if (player.GetPlayerBody()->GetPosition().y < enemyBody[i]->GetPosition().y) {
                    player.GetPlayerBody()->SetLinearVelocity(b2Vec2(0.0f, -10.0f));

                    enemyBody[i]->DestroyFixture(enemyBody[i]->GetFixtureList());
                    enemy.erase(enemy.begin() + i);
                    enemyBody.erase(enemyBody.begin() + i);
                } else {
                    int tmp = (player.GetPlayerBody()->GetPosition().x < enemyBody[i]->GetPosition().x) ? -1 : 1;
                    player.GetPlayerBody()->SetLinearVelocity(b2Vec2(10.0f * float(tmp), 0.0f));
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
}

void Level::Draw(sf::RenderWindow &window) const
{
    for (const auto &layer : layers) {
        for (const auto &tile : layer.GetTilesVector()) {
            window.draw(tile);
        }
    }
    for(const auto & el : enemy) {
        window.draw(el.GetSprite());
    }

    for(const auto & el : coin) {
        window.draw(el.GetSprite());
    }
}
