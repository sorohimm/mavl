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
            if(event.key.code == sf::Keyboard::Space && level.GetPlayerBody()->GetLinearVelocity().y == 0)
                level.GetPlayerBody()->SetLinearVelocity(b2Vec2(0.0f, -15.0f));

            if(event.key.code == sf::Keyboard::D)
                level.GetPlayerBody()->SetLinearVelocity(b2Vec2(150.0f, 0.0f));

            if(event.key.code == sf::Keyboard::A)
                level.GetPlayerBody()->SetLinearVelocity(b2Vec2(-150.0f, 0.0f));
            break;
    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//        Player.moveRight();
//        Player.velocityX = 11;
//    } else {
//        Player.velocityY = 0;
//        Player.stopRight();
//    }
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//        Player.velocityX = -11;
//        Player.moveLeft();
//    } else {
//        Player.velocityY = 0;
//        Player.stopLeft();
//    }
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//        Player.velocityY = -40;
//    }
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
//        Player.toBegin();
//    }
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
//        Window.close();
//    }
}


//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//        Player.State = Player::MoveLeft;
//        Player.speed = 8;
//        //currentFrame += 0.005*time;
//        //if (currentFrame > 3) currentFrame -= 3;
//        //p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 135, 96, 54));
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//        Player.State = Player::MoveRight;
//        Player.speed = -8;
//        //	currentFrame += 0.005*time;
//        //	if (currentFrame > 3) currentFrame -= 3;
//        //	p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 232, 96, 54));
//    }
//
//    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (Player.isOnGround)) {
//        Player.State = Player::Jump;
//        Player.accelerationY = -0.4;
//        Player.isOnGround = false;
//        //currentFrame += 0.005*time;
//        //if (currentFrame > 3) currentFrame -= 3;
//        //p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
//    }
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//        Player.State = Player::MoveDown;
//        Player.accelerationY = 0.1;
//
//        //currentFrame += 0.005*time;
//        //if (currentFrame > 3) currentFrame -= 3;
//        //p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
//    }
