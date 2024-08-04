//
// Created by elito on 7/24/2024.
//

#pragma once
#include <memory>

#include "World/World.h"

namespace ecs {

    class ECSCore {
    public:
        static std::shared_ptr<World> GetCurrentWorld();
        static void SetCurrentWorld(const std::shared_ptr<World>& world);

    private:
        static std::shared_ptr<World> m_currentWorld;
    };

} // ecs
