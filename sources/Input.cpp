//
// Copyright © 2020 Vladimir Mashir
//

#include "Engine.h"

void Engine::input()
{
    b2Vec2 velocity = level.GetPlayerBody()->GetLinearVelocity();
    bool is_inputting = false;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        is_inputting = true;
        velocity.y -= 15.0f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        is_inputting = true;
        velocity.x += 150.0f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        is_inputting = true;
        velocity.x -= 150.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        Window.close();
    }
    if (!is_inputting && velocity.x) {
        if (velocity.x > 0) {
            velocity.x -= 5.0f;
        } else {
            velocity.x += 5.0f;
        }
    }
    level.GetPlayerBody()->SetLinearVelocity(velocity);
}

/*
        //currentFrame += 0.005*time;
        //if (currentFrame > 3) currentFrame -= 3;
        //p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
*/
