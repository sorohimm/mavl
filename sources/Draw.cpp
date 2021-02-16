//
// Copyright © 2020 Vladimir Mashir.
//

#include "Engine.h"

void Engine::draw()
{
    Window.clear(sf::Color::Cyan);
    Window.setView(view);
    level.Draw(Window);
    Window.draw(level.GetPlayer().GetSprite());
    Window.display();
}
