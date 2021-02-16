//
//  Copyright © 2020 Vladimir Mashir.
//

#ifndef GAYENGINE_LEVEL_H
#define GAYENGINE_LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <Player.h>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Object
{
private:
    int GetPropertyInt(std::string &input);
    float GetPropertyFloat(std::string &input);
    std::string GetPropertyString(const std::string &input);
    std::string name;
    std::string type;
    sf::Rect<int> rect;
    std::map<std::string, std::string> properties;
    sf::Sprite sprite;

public:
    sf::Rect<int> GetRect() const;
    std::string GetName() const;
    sf::Sprite GetSprite() const;
    void SetName(std::string&);
    void SetType(std::string&);
    void SetSprite(sf::Sprite&);
    void SetRect(sf::Rect<int>&);
};

class Layer: public Player
{
private:
    int opacity;
    std::vector<sf::Sprite> tiles;

public:
    [[nodiscard]] std::vector<sf::Sprite> GetTilesVector() const;
    [[nodiscard]] int GetOpacity() const;
    template <class T>
    void SetOpacity(T&);
    void SetSprite(sf::Sprite&);
};

class Level
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

    std::vector<Object> enemy;
    std::vector<b2Body*> enemyBody;

    std::vector<Object> coin;
    std::vector<b2Body*> coinBody;

    b2Vec2 gravity;
    b2World* world;

public:
    Player GetPlayer();
    bool LoadLevel(std::string&);
    Object GetObject(const std::string&);
    std::vector<Object> GetObjects(const std::string&);
    sf::Vector2i GetTileSize() const;
    void Draw(sf::RenderWindow&);
    void LevelUpdate(sf::View&, const sf::Vector2i&);
    void initObjects(Level&);

    Level();
};

#endif //GAYENGINE_LEVEL_H
