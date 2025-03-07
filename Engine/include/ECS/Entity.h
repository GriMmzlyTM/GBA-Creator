//
// Created by elito on 7/24/2024.
//

#pragma once

#include "ECSConstants.h"
#include "World.h"

namespace ecs {

// Forward declare World.h
class World;

class IEntityBase : ecs::WorldObject {

public:
  ~IEntityBase() = default;
  IEntityBase();
  explicit IEntityBase(EntityID Id);
  IEntityBase(EntityName Name, EntityID Id, const World *World);

  [[nodiscard]] bool IsIdentifierValid() const;

  explicit operator EntityID() const { return Identifier; }

  [[nodiscard]] std::string ToString() const {
      return Name + " - " + std::to_string(Identifier);
  }

  bool operator==(const IEntityBase &Entity) const {
    return Entity.Identifier == Identifier;
  }

  bool operator==(const EntityID Id) const { return Id == Identifier; }

public:
  [[maybe_unused]] static const IEntityBase INVALID_ENTITY;
  EntityName Name;
  EntityID Identifier;

private:
  const World *m_owningWorld;
};

template <IsEntityComponent TComponent0, IsEntityComponent... TComponents>
struct EntityDefinition : public IEntityBase {};

} // namespace ecs
