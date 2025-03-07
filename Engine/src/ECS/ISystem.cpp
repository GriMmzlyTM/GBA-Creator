#include "ISystem.h"

void ecs::ISystem::SetActive(bool bActive) {
    m_bIsActive = bActive;
}

bool ecs::ISystem::IsActive() const {
    return m_bIsActive;
}

void ecs::ISystem::ProcessEntity(const ecs::IEntityBase& entity) const {
    ProcessEntity_Internal(entity); 
}
