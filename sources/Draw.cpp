//
// Copyright © 2020 Vladimir Mashir. All rights reserved.
//

#include "Engine.h"

void Engine::draw()
{
    Window.clear(sf::Color::White);

    std::string fileName = "../GayEngine/map.tmx";
    Level.LoadFromFile(fileName);

    Level.Draw(Window);

    Window.display();
}