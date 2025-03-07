#include "SystemManager.h"

void ecs::SystemManager::ExecuteDraw(const ecs::IEntityBase& entity) const {
    for (const std::unique_ptr<ISystem>& drawSystem : m_drawSystems) {
        drawSystem->ProcessEntity(entity);
    }
}

void ecs::SystemManager::ExecuteUpdate(const ecs::IEntityBase& entity) const {
    for (const std::unique_ptr<ISystem>& updateSystem : m_updateSystems) {
        updateSystem->ProcessEntity(entity);
    }
}
