//
// Copyright © 2020 Vladimir Mashir. All rights reserved.
//

#include "Engine.h"

void Engine::draw()
{
    Window.clear(); //sf::Color::White

    Level.LoadFromFile("../GayEngine/levels/map.tmx");

    Level.Draw(Window);

    Window.display();
}