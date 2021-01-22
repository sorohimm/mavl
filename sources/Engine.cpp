//
// Copyright © 2020 Vladimir Mashir. All rights reserved.
//

#include "Engine.h"

//Engine::Engine() {
//
////    sf::Vector2f resolution;
////    resolution.x = sf::VideoMode::getDesktopMode().width;
////    resolution.y = sf::VideoMode::getDesktopMode().height;
//
//}

void Engine::start()
{
    Window.create(sf::VideoMode(480, 240), "Mavl");  // sf::Style::Fullscreen
    Window.setFramerateLimit(60);

//    b2Vec2 Gravity(0.0f, 1.0f);
//    b2World World(Gravity);

    while (Window.isOpen()) {
        sf::Event Event;

        while (Window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                Window.close();
            }
        }

        input();
        update();
        draw();
    }
}

