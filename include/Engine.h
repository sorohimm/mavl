//
// Copyright © 2020 Vladimir Mashir. All rights reserved.
//

#ifndef GAYENGINE_ENGINE_H
#define GAYENGINE_ENGINE_H

//#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <Level.h>
#include <Player.h>

class Engine
{
private:
    sf::RenderWindow Window;

    Player Player;
    Level Level;

    void input();
    void update();
    void draw();

public:
//    Engine();
    void start();
};

#endif //GAYENGINE_ENGINE_H
