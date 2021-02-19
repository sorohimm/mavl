//
// Copyright © 2020 Vladimir Mashir
//

#include "Engine.h"

void Engine::EngineUpdate() {
    level.LevelUpdate(view, screenSize);
    level.GetPlayer().Update(view, screenSize);
    auto playerPos = level.GetPlayer().GetBody()->GetPosition();
}
