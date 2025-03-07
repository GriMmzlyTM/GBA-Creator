//
// Created by elito on 7/20/2024.
//
#pragma once

#include <memory>

namespace ecs {
    class World;
}

namespace core {

/// Core engine class, this is what handles the game loop and initializing core
/// systems
/// @class
class GBAEngine {

  /// Run data-only modifications of objects
  /// This runs every
  void Update();

  void Draw();

public:
  ecs::World *InitializeWorld();
  [[noreturn]] void StartWorld(ecs::World *world) const;

  ecs::World* GetCurrentWorld();

  //GBAEngine();
  ~GBAEngine();

private:
  ecs::World* m_world;
};

static GBAEngine* GEngine = new GBAEngine();

} // namespace core
