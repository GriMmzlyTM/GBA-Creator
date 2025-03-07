//
// Created by elito on 7/28/2024.
//

#pragma once

#include <map>
#include <memory>
#include <queue>
#include <set>
#include <utility>

#include "ComponentContainer.h"
#include "Entity.h"
#include "World.h"


#include "tonc.h"

namespace ecs {
class EntityManager : public ecs::WorldObject {

public:
  template <IsEntityComponent TComponent0, IsEntityComponent... TComponents>
  IEntityBase CreateEntity(EntityName Name) {
    return CreateEntity(Name, TComponent0(), TComponents()...);
  }

  template <IsEntityComponent TComponent0, IsEntityComponent... TComponents>
  IEntityBase CreateEntity(EntityName Name,
                                         TComponent0 Component0,
                                         TComponents... Components) {
    IEntityBase newEntity(std::move(Name), GetNextFreeID(), GetWorld());

    AddComponentToContainer<TComponent0>(newEntity, Component0);
    (AddComponentToContainer(newEntity, Components) && ...);

    m_Entities.insert(m_Entities.begin() + newEntity.Identifier,
                      std::make_unique<IEntityBase>(newEntity));
    m_assignedIDs.insert(newEntity.Identifier);
    return newEntity;
  }

  [[nodiscard]] IEntityBase FindEntity(EntityID Identifier) const;
  [[nodiscard]] std::vector<IEntityBase> FindEntities(EntityName Name) const;

  [[nodiscard]] std::vector<IEntityBase> GetAllEntities() const;

  /// Finds and returns all entities that match a certain type
  /// Don't do this (Or, don't do it often) as it's much slower
  /// @tparam TEntity Entity type you're trying to find
  /// @return
  template <IsEntity TEntity>
  std::vector<std::weak_ptr<TEntity>> FindEntitiesOfType() {
    // TODO: Implement
    return {};
  }

  template <IsEntityComponent TComponent>
  [[nodiscard]] bool HasActiveComponentForEntity(const IEntityBase &Entity) const {
    bool outSuccess;
    TComponent comp = FindComponentForEntity<TComponent>(Entity, outSuccess);
    return outSuccess && comp.bIsActive;
  }

  template <IsEntityComponent TComponent>
  TComponent FindComponentForEntity(const IEntityBase &Entity,
                                    bool &OutSuccess) const {
    if (!Entity.IsIdentifierValid()) {
      OutSuccess = false;
      return TComponent();
    }

    EntityComponentType compType = TComponent::GetComponentType();
      for (const auto& comp : m_Components) {
        if (comp.first == compType) {
            auto container = dynamic_cast<ComponentContainer<TComponent> *>(comp.second.get());

            // Where the magic happens
            TComponent component = container->GetComponent(Entity.Identifier, OutSuccess);
            return component;
        }
      }
    //auto componentContainerIterator = m_Components.find(compType);
    if (!OutSuccess) {
      OutSuccess = false;
      return TComponent();
    }

    // We assume the component container HAS to be of TComponent type
    //auto container = dynamic_cast<ComponentContainer<TComponent> *>(componentContainerIterator->second.get());

//    TComponent component = container->GetComponent(Entity.Identifier, OutSuccess);
//    return component;
  }

  template <IsEntityComponent TComponent>
  bool AddComponentToContainer(const IEntityBase &Id, TComponent component) {
    if (!Id.IsIdentifierValid()) {
      // TODO: Add err
      return false;
    }

    EntityComponentType compType = TComponent::GetComponentType();
    auto componentContainerIterator = m_Components.find(compType);
    if (componentContainerIterator == m_Components.end()) {
      m_Components[compType] = std::make_shared<ComponentContainer<TComponent>>();
      componentContainerIterator = m_Components.find(compType);
    }
    ComponentContainer<TComponent> *container;
    container = dynamic_cast<ComponentContainer<TComponent> *>(componentContainerIterator->second.get());
    if (container == nullptr) {
      return false;
    }
    container->UpdateComponent(Id.Identifier, component);
    return true;
  }

private:
  EntityID GetNextFreeID();
  void ExpandEntitiesArray();

private:
  std::vector<std::unique_ptr<IEntityBase>> m_Entities;
  std::map<EntityComponentType, std::shared_ptr<ecs::IComponentContainer>> m_Components;
  std::set<int> m_assignedIDs;
  std::queue<int> m_FreeIds;
};

} // namespace ecs
