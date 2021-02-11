//
// Copyright © 2020 Vladimir Mashir
//

#include <Engine.h>

sf::Vector2i Engine::GetScreenSize() {
    return screenSize;
}

Engine::Engine()
{
    screenSize.x = 1120;
    screenSize.y = 656;
    Window.create(sf::VideoMode(screenSize.x, screenSize.y), "*end");
    Window.setFramerateLimit(60);

    view.reset(sf::FloatRect(0.0f, 0.0f, screenSize.x, screenSize.y));
    view.setViewport(sf::FloatRect(0.0f, 0.0f, 3.0f, 3.0f));
//    view.setSize(sf::Vector2f(1920.0f, 1088.0f));
}

void Engine::start()
{
    std::string filename = "levels/start_level/map1.json";

    level.LoadFile(filename);
    level.initObjects(level);

    while (Window.isOpen()) {
        sf::Event event;
        while(Window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                Window.close();
            }
        }
        input();
        level.update(view, screenSize);
        draw();
    }
}
