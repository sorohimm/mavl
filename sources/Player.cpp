//
// Copyright © 2020 Vladimir Mashir
//

#include <Player.h>
#include <iostream>

Player::Player()
{
    texture.loadFromFile("cockBall.png");
    sprite.setTexture(texture);
    textureSize.x = texture.getSize().x;
    textureSize.y = texture.getSize().y;
    sprite.setScale(0.05, 0.05);
    sprite.setOrigin(textureSize.x / 1.5f, textureSize.y / 2.0f);
}

void Player::PlayerUpdate(sf::View& view, const sf::Vector2i& screenSize)
{
    playerBody->GetWorldCenter();
    b2Vec2 pos = playerBody->GetPosition();
    pos.x *= 32.0f;
    pos.y *= 32.0f;
    //std::cout << "player pos: " << pos.x << ", " << pos.y << ";";
    view.setCenter(pos.x + screenSize.x / 3.0f,
                   pos.y + screenSize.y / 3.0f);
    sprite.setPosition(pos.x + 12.0f, pos.y + 8.0f);
    //std::cout << "  " << "sprite pos: " << sprite.getPosition().x  << ", " << sprite.getPosition().y << ";" << std::endl;
}

void Player::SetRect(sf::Rect<int> &inputRect)
{
    rect = inputRect;
}

const sf::Rect<int>& Player::GetRect() const
{
    return rect;
}

const sf::Sprite& Player::GetSprite() const
{
    return sprite;
}

b2Body* Player::GetPlayerBody()
{
    return playerBody;
}
