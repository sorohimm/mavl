//
// Copyright © 2020 Vladimir Mashir
//

#ifndef GAYENGINE_ENGINE_H
#define GAYENGINE_ENGINE_H

#include <SFML/Graphics.hpp>
#include <World.h>

class Engine: public World
{
private:
    sf::Vector2i screenSize;
    bool is_inputting;
    sf::RenderWindow Window;
    World level;
    sf::View view;
    void input();
    void draw();
    void EngineUpdate();

public:
    void start();
    Engine();
};

#endif //GAYENGINE_ENGINE_H
