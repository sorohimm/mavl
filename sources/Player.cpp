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
    sprite.setOrigin(textureSize.x, textureSize.y);
}

void Player::PlayerUpdate(sf::View& view, const sf::Vector2i& screenSize)
{
    playerBody->GetWorldCenter();
    b2Vec2 pos = playerBody->GetPosition();
    std::cout << "player pos: " << pos.x << ", " << pos.y << ";";
    view.setCenter(pos.x + screenSize.x / 3,
                   pos.y + screenSize.y / 3);
    sprite.setPosition(pos.x, pos.y);
    std::cout << "  " << "sprite pos: " << sprite.getPosition().x  << ", " << sprite.getPosition().y << ";" << std::endl;
}

void Player::SetRect(sf::Rect<int> &inputRect)
{
    rect = inputRect;
}

sf::Rect<int> Player::GetRect() const
{
    return rect;
}

sf::Sprite Player::GetSprite()
{
    return sprite;
}

b2Body* Player::GetPlayerBody()
{
    return playerBody;
}
