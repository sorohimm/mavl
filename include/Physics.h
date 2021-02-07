//
//  Copyright © 2020 Vladimir Mashir.
//

#ifndef GAYENGINE_PHYSICS_H
#define GAYENGINE_PHYSICS_H

#include <SFML/Graphics.hpp>

class Physics
{
public:
//    Physics();

    const float groundHeight = 720;
    const float gravity = 3.5;

    float velocityX;
    float velocityY;
    float accelerationX;
    float accelerationY;
};
#endif //GAYENGINE_PHYSICS_H
