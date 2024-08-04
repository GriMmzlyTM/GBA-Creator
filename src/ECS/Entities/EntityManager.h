//
// Created by elito on 7/28/2024.
//

#pragma once

#include <memory>
#include <queue>
#include <set>

#include "Entity.h"

namespace ecs::Entity {
    class EntityManager {

    public:
        template<IsEntity TEntity>
        [[nodiscard]]  std::weak_ptr<TEntity> CreateEntity(EntityName Name) {
            std::shared_ptr<TEntity> newEntity = std::make_shared<TEntity>(Name, GetNextFreeID());

            m_Entities.insert(m_Entities.begin() + newEntity->Identifier, newEntity);
            m_assignedIDs.insert(newEntity->Identifier);
            return newEntity;
        }

        template<IsEntityComponent TComponent0, IsEntityComponent... TComponents>
        [[nodiscard]] std::weak_ptr<EntityDefinition<TComponent0, TComponents...>> CreateEntity(EntityName Name, TComponent0 Component0, TComponents... Components) {
            std::shared_ptr<EntityDefinition<TComponent0, TComponents...>> newEntity = std::make_shared<EntityDefinition<TComponent0, TComponents...>>(Name, GetNextFreeID(), Component0, Components...);

            m_Entities.insert(m_Entities.begin() + newEntity->Identifier, newEntity);
            m_assignedIDs.insert(newEntity->Identifier);
            return newEntity;
        }

        std::weak_ptr<IEntityBase> FindEntity(EntityID Identifier) const;
        std::vector<std::weak_ptr<IEntityBase>> FindEntities(EntityName Name) const;

        
        [[nodiscard]] std::vector<std::weak_ptr<IEntityBase>> GetAllEntities() const;
        
        /// Finds and returns all entities that match a certain type
        /// Don't do this (Or, don't do it often) as it's much slower
        /// @tparam TEntity Entity type you're trying to find
        /// @return 
        template<IsEntity TEntity>
        std::vector<std::weak_ptr<TEntity>> FindEntitiesOfType() {
            // TODO: Implement
            return {};
        }
        
    private:
        EntityID GetNextFreeID();
        void ExpandEntitiesArray();

    private:
        std::vector<std::shared_ptr<IEntityBase>> m_Entities;
        std::set<int> m_assignedIDs;
        std::queue<int> m_FreeIds;
    };

}