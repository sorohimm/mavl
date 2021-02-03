//
// Copyright © 2020 Vladimir Mashir. All rights reserved.
//

#include <Player.h>

Player::Player()
{

    accelerationX = 0;
    accelerationY = 0;

    velocityX = 0;
    velocityY = 0;

    Texture.loadFromFile("../GayEngine/levels/textures/mike_image.png");
    Sprite.setTexture(Texture);
    Sprite.setScale(0.27, 0.27);

    Position.x = 100;
    Position.y = groundHeight;

    isOnGround = true;
}

sf::Sprite Player::getSprite()
{
    return Sprite;
}

void Player::moveLeft()
{
    LeftPressed = true;
}
void Player::moveRight()
{
    RightPressed = true;
}

void Jump()
{

}

void Player::stopLeft()
{
    LeftPressed = false;
}

void Player::stopRight()
{
    RightPressed = false;
}

void Player::stopJump()
{
    LeftPressed = false;
}

void Player::toBegin()
{
    Position.x = 100;
    Position.y = groundHeight;
}

void Player::update()
{
    if (Position.y < groundHeight)
    {
        velocityY += gravity;
    }

    else if (Position.y > groundHeight)
    {
        Position.y = groundHeight;
    }

    if (RightPressed)
    {
        velocityX += accelerationX;
        Position.x += velocityX;
    }

    if (LeftPressed)
    {
        velocityX -= accelerationX;
        Position.x += velocityX;
    }

//    Position.y += velocityY;

    Sprite.setPosition(Position);
}
