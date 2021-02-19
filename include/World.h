//
//  Copyright © 2020 Vladimir Mashir.
//

#ifndef GAYENGINE_WORLD_H
#define GAYENGINE_WORLD_H

#include <string>
#include <vector>
#include "Object.h"
#include <iostream>
#include "Player.h"
#include "Layer.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>

class World
{
private:
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    std::vector<std::pair<std::string, int>> firstTileIDs;

    sf::Rect<float> drawingBounds;
    sf::Texture tileSetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;

    Player player;

    std::vector<std::unique_ptr<Object>> enemy;
    std::vector<std::unique_ptr<Object>> coin;

    b2Vec2 gravity;
    b2World* physicsWorld;

public:
    Player& GetPlayer();
    bool LoadLevel(const std::string&);
    const Object& GetObject(const std::string&) const;
    std::vector<std::unique_ptr<Object>> GetObjects(const std::string&);
    const sf::Vector2i GetTileSize() const;
    void Draw(sf::RenderWindow&) const;
    void LevelUpdate(sf::View&, const sf::Vector2i&);
    void initObjects(World&);

    World();
};

#endif //GAYENGINE_WORLD_H

