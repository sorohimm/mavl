//
// Copyright © 2020 Vladimir Mashir. All rights reserved.
//

#ifndef GAYENGINE_P_H
#define GAYENGINE_P_H

#include <SFML/Graphics.hpp>
#include <Physics.h>

class Player : public Physics
{
private:
    sf::Vector2f Position;
    sf::Sprite Sprite;
    sf::Texture Texture;

    bool isOnGround;
    bool LeftPressed;
    bool RightPressed;
    bool isSelect;
    bool isMove;

public:
    Player();

    sf::Sprite getSprite();

    void moveLeft();
    void moveRight();
    void Jump();

    void stopLeft();
    void stopRight();
    void stopJump();
    void toBegin();

    void update();
};

#endif //GAMEENGINE_P_H
