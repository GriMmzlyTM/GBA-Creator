//
// Created by elito on 7/20/2024.
//

#include "GBAEngine.h"

namespace core {
    [[noreturn]] void GBAEngine::Initialize() {
        m_world = std::make_shared<ecs::World>();
        while (true) {

            // ensure we are not currently drawing to the screen
            // must be in VBLANK
            vid_vsync();

            m_world->ExecuteWorld();
        }
    }

    void GBAEngine::Update() {

    }

    void GBAEngine::Draw() {

    }
} // core