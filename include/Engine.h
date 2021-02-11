//
// Copyright © 2020 Vladimir Mashir
//

#ifndef GAYENGINE_ENGINE_H
#define GAYENGINE_ENGINE_H

#include <SFML/Graphics.hpp>
#include <Level.h>
#include <Player.h>

class Engine
{
public:
    void start();
    sf::Vector2i GetScreenSize();
    Engine();

private:
    sf::RenderWindow Window;

//    Player player;
    Level level;

    void input();
//    void update();
    void draw();

    sf::View view;
    sf::Vector2i screenSize;
};

#endif //GAYENGINE_ENGINE_H
