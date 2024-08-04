//
// Created by elito on 7/24/2024.
//

#pragma once

#include <memory>
#include "../ECSConstants.h"
#include "../Components/IEntityComponent.h"

namespace ecs::Entity {

    struct IEntityBase {
        ~IEntityBase() = default;
        IEntityBase(EntityID id);

        template<IsEntityComponent TComponent>
        TComponent& GetComponent() const;

        template <IsEntityComponent TComponent>
        bool HasComponent() const;

        template<IsEntityComponent TComponent>
        [[nodiscard]] std::shared_ptr<TComponent> GetComponentPtr() const;

        bool IsIdentifierValid() const;

    protected:
        explicit IEntityBase(EntityName Name, EntityID Identifier);

    public:
        EntityName Name;
        EntityID Identifier = -1;
    };

    template<IsEntityComponent TComponent0, IsEntityComponent... TComponents>
    struct EntityDefinition : public IEntityBase {

        explicit EntityDefinition(EntityName Name, EntityID Identifier);
        explicit EntityDefinition(EntityName Name, EntityID Identifier, TComponent0 Component0, TComponents... Components);
    };

    template<IsEntityComponent TComponent0, IsEntityComponent... TComponents>
    EntityDefinition<TComponent0, TComponents...>::EntityDefinition(EntityName Name, EntityID Identifier) : IEntityBase(Name, Identifier) {

    }

    template<IsEntityComponent TComponent0, IsEntityComponent... TComponents>
    EntityDefinition<TComponent0, TComponents...>::EntityDefinition(EntityName Name, EntityID Identifier, TComponent0 Component0, TComponents... Components) : IEntityBase(Name, Identifier) {
        // Get ID assigned
        // Assign components to container
        // Add self to Manager?
    }

} // ecs::entity

DEFINE_COMPONENT_ONE_PARAMETER(RenderComp, int, x)
DEFINE_COMPONENT(TransformComp)
DEFINE_COMPONENT(MovementComp)

typedef ecs::Entity::EntityDefinition<RenderComp, TransformComp> OgreEntity;
typedef ecs::Entity::EntityDefinition<TransformComp> ss;
void T() {
    using namespace ecs::Entity;
    EntityDefinition<RenderComp> Entity("A", 2);

    MovementComp mov;
    TransformComp tr;
    RenderComp r(5);
    OgreEntity RealEntity("Angry Ogre", 3, r, tr);

    std::shared_ptr<RenderComp> comp = RealEntity.GetComponentPtr<RenderComp>();

}
