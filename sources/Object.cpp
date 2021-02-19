#include "Object.h"
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>

// Getters

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

const sf::Rect<float>& Object::GetRect() const
{
    return rect;
}

const std::string& Object::GetName() const
{
    return name;
}

sf::Sprite& Object::GetSprite()
{
    return sprite;
}

sf::Texture& Object::GetTexture() {
    return texture;
}

b2Body* Object::GetBody() {
    return body;
}

// Setters

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

void Object::SetTexture(const sf::Texture &inputTexture) {
    texture = inputTexture;
}

void Object::SetBody(b2Body* new_body) {
    body = new_body;
}

void Object::SetRect(const sf::Rect<float> &inputRect)
{
    rect = inputRect;
}

void Object::Update(sf::View& view, const sf::Vector2i& screenSize)
{
    GetBody()->GetWorldCenter();
    b2Vec2 pos = GetBody()->GetPosition();
    pos.x *= 32.0f;
    pos.y *= 32.0f;
    view.setCenter(pos.x + screenSize.x / 3.0f,
                   pos.y + screenSize.y / 3.0f);
    GetSprite().setPosition(pos.x + 12.0f, pos.y + 8.0f);
}
