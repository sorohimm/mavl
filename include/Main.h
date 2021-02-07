//
//  Copyright © 2020 Vladimir Mashir.
//

#ifndef GAYENGINE_MAIN_H
#define GAYENGINE_MAIN_H

#include <Engine.h>
#include <Level.h>
#include <random>

Object player;
b2Body* playerBody;

std::vector<Object> coin;
std::vector<b2Body*> coinBody;

std::vector<Object> enemy;
std::vector<b2Body*> enemyBody;

#endif //GAYENGINE_MAIN_H
