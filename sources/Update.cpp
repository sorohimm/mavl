//
// Copyright © 2020 Vladimir Mashir
//

#include "Engine.h"

void Engine::EngineUpdate() {
    level.LevelUpdate(view, screenSize);
    level.GetPlayer().PlayerUpdate(view, screenSize);
}