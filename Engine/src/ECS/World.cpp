#include "World.h"
#include "SystemManager.h"
#include "EntityManager.h"

extern "C" {
#include <tonc_input.h>
#include <tonc_video.h>
}

ecs::World::World() {
    m_entityManager = new EntityManager();
    m_systemManager = new SystemManager();
}

ecs::World::~World()
{
    delete m_entityManager;
    delete m_systemManager;
}

[[noreturn]] void ecs::World::ExecuteWorld() const {

    while(true) {
        vid_vsync();

        const std::vector<IEntityBase> entities = m_entityManager->GetAllEntities();

        key_poll();

        // Update loop
        for (const IEntityBase &entity: entities) {
            m_systemManager->ExecuteUpdate(entity);
        }

        // Draw loop
        for (const IEntityBase &entity: entities) {
            m_systemManager->ExecuteDraw(entity);
        }
    }

}

ecs::EntityManager *ecs::World::GetEntityManager() const {
    return m_entityManager;
}

ecs::SystemManager *ecs::World::GetSystemManager() const {
    return m_systemManager;
}

[[maybe_unused]] const ecs::World* ecs::WorldObject::GetWorld() const {
    return m_OwningWorld;
}
