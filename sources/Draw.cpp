//
//  Copyright © 2020 Vladimir Mashir.
//

#include "Engine.h"

void Engine::draw()
{
    Window.clear(); //sf::Color::White
    Window.setView(view);
    Level.Draw(Window);
    Window.display();
}