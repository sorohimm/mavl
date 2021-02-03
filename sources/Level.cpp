//
//  Copyright © 2020 Vladimir Mashir.
//

#include <Level.h>
#include <nlohmann/json.hpp>
#include <fstream>

int Object::GetPropertyInt(std::string &input) {
    return atoi(properties[input].c_str());
}

float Object::GetPropertyFloat(std::string &input) {
    return strtod(properties[input].c_str(), nullptr);
}

std::string Object::GetPropertyString(const std::string &input) {
    return properties[name];
}

bool Level::LoadFromFile(const std::string &filename) {
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

//                float Width;
//                float Height;

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

//                        while (prop) {
//                            std::string propertyName  = prop->Attribute("name");
//                            std::string propertyValue = prop->Attribute("value");
//
//                            object.properties[propertyName] = propertyValue;
//
//                            prop = prop->NextSiblingElement("property");
//                        }

                }

                objects.push_back(thisObject);
            }
        }
    }
    return true;
}

Object Level::GetObject(const std::string &name) {
    for (const auto &el : objects) {
        if (el.name == name) {
            return el;
        }
    }
    return *objects.end();
}

std::vector<Object> Level::GetObjects(const std::string &name) {
    std::vector<Object> vec;
    for (const auto &el : objects) {
        if (el.name == name) {
            vec.push_back(el);
        }
    }
    return vec;
}

sf::Vector2i Level::GetTileSize() {
    return sf::Vector2i(tileWidth, tileHeight);
}

void Level::Draw(sf::RenderWindow &window) {
    for (size_t layer = 0; layer < layers.size(); layer++) {
        for (size_t tile = 0; tile < layers[layer].tiles.size(); tile++) {
            window.draw(layers[layer].tiles[tile]);
        }
    }
}
