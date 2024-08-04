//
// Created by elito on 7/24/2024.
//

#include "ECSCore.h"

namespace ecs {
    std::shared_ptr<World> ECSCore::GetCurrentWorld() {
        return m_currentWorld;
    }

    void ECSCore::SetCurrentWorld(const std::shared_ptr<World>& world) {
        if (world != nullptr) {
            m_currentWorld = world;
        }
    }

} // ecs