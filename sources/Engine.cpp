//
// Copyright © 2020 Vladimir Mashir
//

#include <Engine.h>



Engine::Engine()
{
    screenSize.x = sf::VideoMode::getDesktopMode().width;
    screenSize.y = sf::VideoMode::getDesktopMode().height;
    Window.create(sf::VideoMode(screenSize.x, screenSize.y), "*end", sf::Style::Fullscreen);
    Window.setFramerateLimit(60);

    view.reset(sf::FloatRect(0.0f, 0.0f, screenSize.x, screenSize.y));
    view.setViewport(sf::FloatRect(0.0f, 0.0f, 3.0f, 3.0f));
}

void Engine::start()
{
    std::string filename = "levels/start_level/map1.json";

    level.LoadLevel(filename);
    level.initObjects(level);

    while (Window.isOpen()) {
        sf::Event event;
        while(Window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                Window.close();
            }
        }
        input();
        EngineUpdate();
        draw();
    }
}
