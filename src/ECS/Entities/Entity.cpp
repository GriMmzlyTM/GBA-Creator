//
// Created by elito on 7/24/2024.
//

#include "Entity.h"

namespace ecs::Entity {

    IEntityBase::IEntityBase(EntityName Name, EntityID Identifier) : Name(Name), Identifier(Identifier) {}

    IEntityBase::IEntityBase(EntityID id) : Identifier(id) {
        
    }

    bool IEntityBase::IsIdentifierValid() const {
        return Identifier != -1;
    }


    template<IsEntityComponent TComponent>
    std::shared_ptr<TComponent> IEntityBase::GetComponentPtr() const {
        return nullptr;
    }

    template<IsEntityComponent TComponent>
    TComponent& IEntityBase::GetComponent() const {
        std::shared_ptr<TComponent> pComponent = GetComponentPtr<TComponent>();
        if (pComponent == nullptr) {
            return false;
        }

        return &pComponent.get();
    }

    template<IsEntityComponent TComponent>
    bool IEntityBase::HasComponent() const {
        std::shared_ptr<TComponent> pComponent = GetComponentPtr<TComponent>();
        if (pComponent == nullptr) {
            return false;
        }
        return true;
    }

}; // ecs::entity