//
// Created by elito on 7/20/2024.
//
#pragma once

#include <memory>

#include "tonc.h"
#include "ECS/World/World.h"

namespace core {

    /// Core engine class, this is what handles the game loop and initializing core systems
    /// @class
    class GBAEngine {

        /// Run data-only modifications of objects
        /// This runs every
        void Update();

        void Draw();

    public:
        [[noreturn]] void Initialize();

    private:
        std::shared_ptr<ecs::World> m_world;
    };

} // core
