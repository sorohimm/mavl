//
// Copyright © 2020 Vladimir Mashir
//

#include <Player.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

Player::Player()
{
    GetTexture().loadFromFile("cockBall.png");
    GetSprite().setScale(0.05, 0.05);
    GetSprite().setOrigin(GetTexture().getSize().x / 1.5f, GetTexture().getSize().y / 2.0f);
    GetSprite().setTexture(GetTexture());
}

