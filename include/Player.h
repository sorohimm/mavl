//
//  Copyright © 2020 Vladimir Mashir.
//
#ifndef GAYENGINE_P_H
#define GAYENGINE_P_H

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Player
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2<float> textureSize;
    bool isOnGround;
    sf::Rect<int> rect;

public:
    b2Body* playerBody;
    virtual b2Body* GetPlayerBody();
    void SetRect(sf::Rect<int> &inputRect);
    virtual void PlayerUpdate(sf::View&, const sf::Vector2i&);
    sf::Rect<int> GetRect() const;
    sf::Sprite GetSprite();

    Player();
};

#endif //GAMEENGINE_P_H
