//
// Copyright © 2020 Vladimir Mashir
//

#include <Player.h>

Player::Player()
{
    texture.loadFromFile("bmstu.png");
    sprite.setTexture(texture);
    sprite.setScale(1, 1);

    Position.x = 100;
    Position.y = 100;
    isOnGround = true;
}


void Player::moveLeft()
{
    LeftPressed = true;
}
void Player::moveRight()
{
    RightPressed = true;
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

}

void Player::SetRect(sf::Rect<int> &inputRect) {
    rect = inputRect;
}

sf::Rect<int> Player::GetRect() const {
    return rect;
}

sf::Sprite Player::GetSprite() {
    return sprite;
}