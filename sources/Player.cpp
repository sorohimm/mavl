//
// Copyright © 2020 Vladimir Mashir
//

#include <Player.h>

Player::Player()
{

    Texture.loadFromFile("../GayEngine/levels/textures/.png");
    Sprite.setTexture(Texture);
    Sprite.setScale(3, 3);

    Position.x = 100;
    Position.y = 100;
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
    Position.y = 100;
}

void Player::update()
{
//    if (Position.y < groundHeight)
//    {
//        velocityY += gravity;
//    }
//
//    else if (Position.y > groundHeight)
//    {
//        Position.y = groundHeight;
//    }
//
//    if (RightPressed)
//    {
//        velocityX += accelerationX;
//        Position.x += velocityX;
//    }
//
//    if (LeftPressed)
//    {
//        velocityX -= accelerationX;
//        Position.x += velocityX;
//    }
//
////    Position.y += velocityY;

//    Sprite.setPosition(Position);
}
