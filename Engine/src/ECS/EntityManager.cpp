//
// Created by elito on 7/28/2024.
//

#include "EntityManager.h"


ecs::IEntityBase ecs::EntityManager::FindEntity(EntityID Identifier) const {
    if (Identifier >= m_Entities.capacity()) {
        return IEntityBase::INVALID_ENTITY;
    }
    // TODO: Add check to make sure entity has proper identifier
    return *m_Entities[Identifier].get();
}

std::vector<ecs::IEntityBase> ecs::EntityManager::FindEntities(EntityName Name) const {
    std::vector<ecs::IEntityBase> returnVector;
    for (auto& entity : m_Entities) {
        if (entity->Name == Name) {
            returnVector.push_back(*entity);
        }
    }
    return returnVector;
}

std::vector<ecs::IEntityBase> ecs::EntityManager::GetAllEntities() const {
    std::vector<ecs::IEntityBase> returnVector;
    for(auto validIndex : m_assignedIDs) {
        returnVector.push_back(*m_Entities.at(validIndex));
    }
    return returnVector;
}

ecs::EntityID ecs::EntityManager::GetNextFreeID() {
    if (m_FreeIds.empty()) {
        ExpandEntitiesArray();
    }

    EntityID newId = m_FreeIds.front();
    m_FreeIds.pop();
    return newId;
}

void ecs::EntityManager::ExpandEntitiesArray() {
    auto oldEntitiesSize = m_Entities.capacity();
    m_Entities.resize(oldEntitiesSize + 256);
    for (int i = 0; i < 256; ++i) {
        m_FreeIds.push(oldEntitiesSize + i);
    }
}
