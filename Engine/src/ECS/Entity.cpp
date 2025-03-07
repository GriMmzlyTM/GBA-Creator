//
// Created by elito on 7/24/2024.
//

#include "Entity.h"

namespace ecs {

    [[maybe_unused]] const IEntityBase IEntityBase::INVALID_ENTITY("", -1, nullptr);

    IEntityBase::IEntityBase(EntityName Name, EntityID Id, const World* World) : Name(Name), Identifier(Id) {
    }

    bool IEntityBase::IsIdentifierValid() const {
        return Identifier != INVALID_ENTITY.Identifier;
    }

    IEntityBase::IEntityBase() : Name(INVALID_ENTITY.Name), Identifier(INVALID_ENTITY.Identifier) {
        m_owningWorld = INVALID_ENTITY.m_owningWorld;
    }

    IEntityBase::IEntityBase(EntityID Id) : Name("TMP_ENTITY"), Identifier(Id) {

    }

}; // ecs