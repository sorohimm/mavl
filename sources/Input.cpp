//
// Copyright © 2020 Vladimir Mashir
//

#include "Engine.h"

void Engine::input(sf::Event &event)
{
    switch(event.type) {
        case sf::Event::Closed:
            Window.close();
            break;

        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Space && level.GetPlayerBody()->GetLinearVelocity().y == 0) {
                level.GetPlayerBody()->SetLinearVelocity(b2Vec2(0.0f, -15.0f));
            }

            if(event.key.code == sf::Keyboard::D) {
                level.GetPlayerBody()->SetLinearVelocity(b2Vec2(125.0f, 0.0f));
            }

            if(event.key.code == sf::Keyboard::A) {
                level.GetPlayerBody()->SetLinearVelocity(b2Vec2(-125.0f, 0.0f));
            }

            if(event.key.code == sf::Keyboard::Escape) {
                Window.close();
            }
            break;
    }
}

/*
        //currentFrame += 0.005*time;
        //if (currentFrame > 3) currentFrame -= 3;
        //p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
*/
