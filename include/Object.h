#ifndef GAYENGINE_OBJECT_H
#define GAYENGINE_OBJECT_H

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <box2d/b2_body.h>

class Object
{
private:
    int GetPropertyInt(std::string &input);
    float GetPropertyFloat(std::string &input);
    std::string GetPropertyString(const std::string &input);
    std::string name;
    std::string type;
    sf::Rect<float> rect;
    std::map<std::string, std::string> properties;
    sf::Sprite sprite;
    sf::Texture texture;
    b2Body* body;
    bool isOnGround;

public:
    // Getters
    const sf::Rect<float>& GetRect() const;
    const std::string& GetName() const;
    sf::Sprite& GetSprite();
    sf::Texture& GetTexture();
    b2Body* GetBody();
    // Setters
    void SetBody(b2Body*);
    void SetName(const std::string&);
    void SetType(const std::string&);
    void SetSprite(const sf::Sprite&);
    void SetTexture(const sf::Texture&);
    void SetRect(const sf::Rect<float>&);
    void Update(sf::View&, const sf::Vector2i&);
    Object() {};
};
#endif //GAYENGINE_OBJECT_H

