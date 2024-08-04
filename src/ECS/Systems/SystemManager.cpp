#include "SystemManager.h"

void ecs::System::SystemManager::ExecuteDraw(const std::weak_ptr<Entity::IEntityBase>& entity) const {
    for (const std::unique_ptr<ISystem>& drawSystem : m_drawSystems) {
        drawSystem->ProcessEntity(entity);
    }
}

void ecs::System::SystemManager::ExecuteUpdate(const std::weak_ptr<Entity::IEntityBase>& entity) const {
    for (const std::unique_ptr<ISystem>& updateSystem : m_updateSystems) {
        updateSystem->ProcessEntity(entity);
    }
}
