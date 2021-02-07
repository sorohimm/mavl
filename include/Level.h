//
//  Copyright © 2020 Vladimir Mashir.
//

#ifndef GAYENGINE_LEVEL_H
#define GAYENGINE_LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>

struct Object
{
    int GetPropertyInt(std::string &input);
    float GetPropertyFloat(std::string &input);
    std::string GetPropertyString(const std::string &input);

    std::string name;
    std::string type;
    sf::Rect<int> rect;
    std::map<std::string, std::string> properties;

    sf::Sprite sprite;
};

struct Layer
{
    int opacity;
    std::vector<sf::Sprite> tiles;
};

class Level
{
public:
    bool LoadFromFile(const std::string &filename);
    Object GetObject(const std::string &name);
    std::vector<Object> GetObjects(const std::string &name);
    void Draw(sf::RenderWindow &window);
    sf::Vector2i GetTileSize();

private:
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    int firstTileID;
    std::vector<std::pair<std::string, int>> firstTileIDs;

    sf::Rect<float> drawingBounds;
    sf::Texture tileSetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;
};

#endif //GAYENGINE_LEVEL_H
