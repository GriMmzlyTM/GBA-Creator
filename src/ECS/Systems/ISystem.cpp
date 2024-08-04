#include "ISystem.h"

void ecs::System::ISystem::SetActive(bool bActive) {
    m_bIsActive = bActive;
}

bool ecs::System::ISystem::IsActive() const {
    return m_bIsActive;
}

void ecs::System::ISystem::ProcessEntity(const std::weak_ptr<Entity::IEntityBase>& entity) const {
    ProcessEntity_Internal(entity);
}
