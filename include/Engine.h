//
// Copyright © 2020 Vladimir Mashir
//

#ifndef GAYENGINE_ENGINE_H
#define GAYENGINE_ENGINE_H

#include <SFML/Graphics.hpp>
#include <Level.h>
#include <Player.h>
#include <random>

class Engine
{
private:
    sf::RenderWindow Window;
    sf::Event Event;


    Player Player;
    Level Level;

    void input(sf::Event&);
    void update();
    void draw();

    sf::View view;
    sf::Vector2i screenSize;

public:
    Engine();
    void start();
    sf::Vector2i GetScreenSize();
};

#endif //GAYENGINE_ENGINE_H
