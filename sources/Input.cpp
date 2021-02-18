//
// Copyright © 2020 Vladimir Mashir
//

#include "Engine.h"

void ground_input(b2Vec2& velocity) {
    bool is_inputting = false;
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
    if (!is_inputting) {
        if (velocity.x > 0) {
            velocity.x -= 0.2f;
        } else {
            velocity.x += 0.2f;
        }
        if (std::abs(velocity.x) < 0.5f) {
          velocity.x *= 0.5;
        }
    }
}

void air_input(b2Vec2& velocity) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x += 0.1f;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x -= 0.1f;
    }
}

void clamp(b2Vec2& velocity) {
    if (velocity.x > 10.0f) {
        velocity.x = 10.0f;
    } else if (velocity.x < -10.0f) {
        velocity.x = -10.0f;
    }
    if (velocity.y > 20.0f) {
        velocity.y = 20.0f;
    } else if (velocity.y < -20.0f) {
        velocity.y = -20.0f;
    }
}

void Engine::input()
{
    b2Vec2 velocity = level.GetPlayer().GetPlayerBody()->GetLinearVelocity();
    if (velocity.y == 0) {
      ground_input(velocity);
    } else {
      air_input(velocity);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        Window.close();
    }
    clamp(velocity);
    level.GetPlayer().GetPlayerBody()->SetLinearVelocity(velocity);
}

/*
    currentFrame += 0.005*time;
    if (currentFrame > 3) currentFrame -= 3;
    p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
*/
