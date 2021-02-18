//
// Copyright © 2020 Vladimir Mashir
//

#include "Engine.h"

void Engine::input()
{
    b2Vec2 velocity = level.GetPlayer().GetPlayerBody()->GetLinearVelocity();
    is_inputting = false;
    if (velocity.y == 0) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        is_inputting = true;
        velocity.y -= 5.0f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        is_inputting = true;
        velocity.x += 1.0f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        is_inputting = true;
        velocity.x -= 1.0f;
    }
    if (!is_inputting && bool(velocity.x)) {
        if (velocity.x > 0) {
            velocity.x -= 0.5f;
        } else {
            velocity.x += 0.5f;
        }
        if (std::abs(velocity.x) < 0.5f) {
          velocity.x *= 0.5;
        }
    }

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        Window.close();
    }
    level.GetPlayer().GetPlayerBody()->SetLinearVelocity(velocity);
}

/*
    currentFrame += 0.005*time;
    if (currentFrame > 3) currentFrame -= 3;
    p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
*/
