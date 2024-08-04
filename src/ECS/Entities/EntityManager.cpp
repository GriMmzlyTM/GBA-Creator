//
// Created by elito on 7/28/2024.
//

#include "EntityManager.h"


std::weak_ptr<ecs::Entity::IEntityBase> ecs::Entity::EntityManager::FindEntity(EntityID Identifier) const {
    if (Identifier >= m_Entities.capacity()) {
        return {};
    }
    // TODO: Add check to make sure entity has proper identifier
    return m_Entities[Identifier];
}

std::vector<std::weak_ptr<ecs::Entity::IEntityBase>> ecs::Entity::EntityManager::FindEntities(EntityName Name) const {
    std::vector<std::weak_ptr<IEntityBase>> returnVector;
    for (const std::shared_ptr<IEntityBase>& entity : m_Entities) {
        if (entity->Name == Name) {
            returnVector.push_back(entity);
        }
    }
    return returnVector;
}

std::vector<std::weak_ptr<ecs::Entity::IEntityBase>> ecs::Entity::EntityManager::GetAllEntities() const {
    std::vector<std::weak_ptr<IEntityBase>> returnVector;
    for(auto validIndex : m_assignedIDs) {
        returnVector.push_back(m_Entities.at(validIndex));
    }
    return returnVector;
}

ecs::EntityID ecs::Entity::EntityManager::GetNextFreeID() {
    if (m_FreeIds.empty()) {
        ExpandEntitiesArray();
    }

    EntityID newId = m_FreeIds.front();
    m_FreeIds.pop();
    return newId;
}

void ecs::Entity::EntityManager::ExpandEntitiesArray() {
    auto oldEntitiesSize = m_Entities.capacity();
    m_Entities.resize(oldEntitiesSize + 256);
    for (int i = 0; i < 256; ++i) {
        m_FreeIds.push(oldEntitiesSize + i);
    }
}
