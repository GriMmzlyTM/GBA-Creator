//
// Created by elito on 7/24/2024.
//

#pragma once

#include "ECSConstants.h"
#include <map>
#include <queue>
#include <vector>

namespace ecs {

class IComponentContainer {
public:
  [[nodiscard]] virtual EntityComponentType GetSupportedComponentType() const {
    return "INVALID_COMPONENT_CONTAINER";
  }

  IComponentContainer() = default;
};

///
/// \tparam TComponent
template <IsEntityComponent TComponent>
class ComponentContainer : public IComponentContainer {

  /// EntityID - Component - MaxSize
  std::map<EntityID, TComponent> m_components;

  // May not be required?
  const std::vector<TComponent> m_componentsBuffer;

  const std::queue<int> m_removedEntities;
  const std::queue<int> m_addedEntities;
  const std::queue<int> m_updatedEntities;

public:
  ComponentContainer() = default;

  ///
  /// \param Id
  /// \return
  [[nodiscard]] TComponent GetComponent(EntityID Id, bool &OutSuccess) const {
    const auto desiredComp = m_components.find(Id);
    if (desiredComp != m_components.end()) {
      OutSuccess = true;
      return desiredComp->second;
    }
    OutSuccess = false;
    return TComponent();
  }

  ///
  /// \return
  [[nodiscard]] EntityComponentType GetSupportedComponentType() const override {
    return TComponent::GetComponentType();
  }

  ///
  /// \param entityId
  /// \param component
  void UpdateComponent(EntityID entityId, TComponent &component) {
    // TODO: Temporary, look into buffering
    m_components.insert_or_assign(entityId, component);
  }
};
} // namespace ecs
