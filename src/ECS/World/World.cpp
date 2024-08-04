#include "World.h"

ecs::World::World() {
    m_entityManager = std::make_unique<Entity::EntityManager>();
    m_systemManager = std::make_unique<System::SystemManager>();
}

void ecs::World::ExecuteWorld() const {
    const std::vector<std::weak_ptr<Entity::IEntityBase>> entities = m_entityManager->GetAllEntities();

    // Update loop
    for (const std::weak_ptr<Entity::IEntityBase>& entity : entities) {
        m_systemManager->ExecuteUpdate(entity);
    }

    // Draw loop
    for (const std::weak_ptr<Entity::IEntityBase>& entity : entities) {
        m_systemManager->ExecuteDraw(entity);
    }

}

std::weak_ptr<ecs::Entity::IEntityBase> ecs::World::GetEntity(EntityID entityID) const {
    return m_entityManager->FindEntity(entityID);
}
