#pragma once

#include <memory>
#include "GBAEngine.h"

namespace ecs {

class EntityManager;
class SystemManager;
class IEntityBase;

class World {

  EntityManager* m_entityManager;
  SystemManager* m_systemManager;

public:
  World();
  ~World();

  [[nodiscard]] EntityManager *GetEntityManager() const;
  [[nodiscard]] SystemManager *GetSystemManager() const;

  [[noreturn]] void ExecuteWorld() const;
};

// A WorldObject is an object that belongs to, and is managed by a World.
// WorldObjects know which world they belong to and are automatically disabled
// when the world is no longer the current active world.
class WorldObject {

public:
  [[maybe_unused]] [[nodiscard]] const World *GetWorld() const;

protected:
    WorldObject() {
        m_OwningWorld = core::GEngine->GetCurrentWorld();
    }

private:

    World* m_OwningWorld;
};
} // namespace ecs
