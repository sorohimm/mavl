//
//  Copyright © 2020 Vladimir Mashir. All rights reserved.
//

#include <Level.h>
#include <tinyxml.h>

int Object::GetPropertyInt(std::string name)
{
    return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(std::string name)
{
    return strtod(properties[name].c_str(), nullptr);
}

std::string Object::GetPropertyString(std::string name)
{
    return properties[name];
}

bool Level::LoadFromFile(std::string filename)
{
    TiXmlDocument levelFile(filename.c_str());

    // загружаем карту
    if (!levelFile.LoadFile()) {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }

    // работаем с контейнером map
    TiXmlElement *map;
    map = levelFile.FirstChildElement("map");

    // мапа: <map version="1.0" orientation="orthogonal"
    // width="10" height="10" tilewidth="34" tileheight="34">
    width      = atoi(map->Attribute("width"));
    height     = atoi(map->Attribute("height"));
    tileWidth  = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    // тайлсет и идентификатор первого тайла
    TiXmlElement *tileSetElement;
    tileSetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tileSetElement->Attribute("firstgid"));

    // source - путь до картинки в контейнере image
    TiXmlElement *image;
    image = tileSetElement->FirstChildElement("image");
    std::string imagePath = image->Attribute("source");

    // загрузка тайлсета
    sf::Image img;

    if (!img.loadFromFile(imagePath)) {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }

    // очищаем карту от света (109, 159, 185)
    img.createMaskFromColor(sf::Color(109, 159, 185));
    // загрузка текстуру из изображения
    tileSetImage.loadFromImage(img);
    // расплывчатость запрещена
    tileSetImage.setSmooth(false);

    // количество столбцов и строк тайлсета
    int columns = tileSetImage.getSize().x / tileWidth;
    int rows    = tileSetImage.getSize().y / tileHeight;

    // вектор из прямоугольников изображений (TextureRect)
    std::vector<sf::Rect<int>> subRects;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            sf::Rect<int> rect;

            rect.top    = y * tileHeight;
            rect.height = tileHeight;
            rect.left   = x * tileWidth;
            rect.width  = tileWidth;

            subRects.push_back(rect);
        }
    }

    // обработка слоев
    TiXmlElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement) {
        Layer layer;

        // если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
        if (layerElement->Attribute("opacity") != nullptr) {
            float opacity = strtod(layerElement->Attribute("opacity"), nullptr);
            layer.opacity = 255 * opacity;
        } else {
            layer.opacity = 255;
        }

        // контейнер <data>
        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == nullptr) {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        // контейнер tile - описание тайлов каждого слоя
        TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == nullptr) {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while (tileElement) {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;

            // устанавливаем TextureRect каждого тайла
            if (subRectToUse >= 0) {
                sf::Sprite sprite;
                sprite.setTexture(tileSetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileWidth, y * tileHeight);
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= width) {
                x = 0;
                y++;
                if (y >= height)
                    y = 0;
            }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    // обработка объектов
    TiXmlElement *objectGroupElement;

    // если есть слои объектов
    if (map->FirstChildElement("objectgroup") != nullptr) {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement) {
            // контейнер <object>
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement) {
                // получаем все данные - тип, имя, позиция, etc
                std::string objectType;
                if (objectElement->Attribute("type") != nullptr) {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != nullptr) {
                    objectName = objectElement->Attribute("name");
                }
                float x = atoi(objectElement->Attribute("x"));
                float y = atoi(objectElement->Attribute("y"));

//                int width;
//                int height;

                sf::Sprite sprite;
                sprite.setTexture(tileSetImage);
                sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != nullptr) {
                    width  = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                } else {
                    width  = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
                }

                // экземпляр объекта
                Object object;
                object.name   = objectName;
                object.type   = objectType;
                object.sprite = sprite;

                sf::Rect<int> objectRect;
                objectRect.top    = y;
                objectRect.left   = x;
                objectRect.height = height;
                objectRect.width  = width;
                object.rect       = objectRect;

                // "переменные" объекта
                TiXmlElement *properties;
                properties = objectElement->FirstChildElement("properties");

                if (properties != nullptr) {
                    TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != nullptr) {
                        while (prop) {
                            std::string propertyName  = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                // пихаем объект в вектор
                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    } else {
        std::cout << "layers not found..." << std::endl;
    }

    return true;
}

Object Level::GetObject(std::string name)
{
    for (const auto &el : objects) {
        if (el.name == name) {
            return el;
        }
    }
    return *objects.end();
}

std::vector<Object> Level::GetObjects(std::string name)
{
    std::vector<Object> vec;
    for (const auto &el : objects) {
        if (el.name == name) {
            vec.push_back(el);
        }
    }
    return vec;
}

sf::Vector2i Level::GetTileSize()
{
    return sf::Vector2i(tileWidth, tileHeight);
}

void Level::Draw(sf::RenderWindow &window)
{
    for (size_t layer = 0; layer < layers.size(); layer++) {
        for (size_t tile = 0; tile < layers[layer].tiles.size(); tile++) {
            window.draw(layers[layer].tiles[tile]);
        }
    }
}