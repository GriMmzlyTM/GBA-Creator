//
// Created by elito on 7/29/2024.
//

#pragma once

#include "ECSConstants.h"
#include "Entity.h"
#include "EntityManager.h"

namespace ecs {
    
    class ISystem : public WorldObject {
    public:
        virtual ~ISystem() = default;

        void SetActive(bool bActive);
        [[nodiscard]] bool IsActive() const;

        void ProcessEntity(const ecs::IEntityBase& entity) const;
    protected:
        ISystem(): WorldObject() {};
        virtual void ProcessEntity_Internal(const ecs::IEntityBase& entityId) const = 0;

    protected:
        bool m_bIsActive = true;

    };

    /// System base
    /// @tparam TComponents 
    template<IsEntityComponent... TComponents>
    class SystemBase : public ISystem {

    protected:

        SystemBase() : ISystem() {

        }

        [[nodiscard]] bool EntityMatchesSystem(const ecs::IEntityBase& Entity) const {
            if (Entity == IEntityBase::INVALID_ENTITY) {
                // TODO: Error? Something?
                return false;
            }

            EntityManager* entityManager = GetWorld()->GetEntityManager();
            return (... && entityManager->HasActiveComponentForEntity<TComponents>(Entity));
        }
    };

    /// Update System
    /// @tparam TComponents 
    template<IsEntityComponent... TComponents>
    class IUpdateSystem : public SystemBase<TComponents...> {
        using Super = SystemBase<TComponents...>;
    public:
        IUpdateSystem() : Super() {}
        ~IUpdateSystem()  = default;
        virtual void Update(const IEntityBase& Entity, TComponents... Components) const = 0;

    protected:
        void ProcessEntity_Internal(const IEntityBase& Entity) const override {
            // We get all components once to check, this is probably very bad for performance
            if (!Super::EntityMatchesSystem(Entity)) {
                return;
            }

            EntityManager* entityManager = Super::GetWorld()->GetEntityManager();
            bool OutSuccess;
            Update(Entity, entityManager->FindComponentForEntity<TComponents>(Entity, OutSuccess)...);
        }
    };

    /// Draw system
    /// @tparam TComponents 
    template<IsEntityComponent... TComponents>
    class IDrawSystem : public SystemBase<TComponents...> {
        using Super = SystemBase<TComponents...>;
    public:
        IDrawSystem() : Super() {};
        ~IDrawSystem() override = default;
        virtual void Draw(const IEntityBase& Entity, TComponents...Components) const = 0;

    protected:
        void ProcessEntity_Internal(const ecs::IEntityBase& Entity) const override {

            // We get all components once to check, this is probably very bad for performance
            if (!Super::EntityMatchesSystem(Entity)) {
                return;
            }

            EntityManager* entityManager = Super::GetWorld()->GetEntityManager();
            bool OutSuccess;
            Draw(Entity, entityManager->FindComponentForEntity<TComponents>(Entity, OutSuccess)...);
        }
    };
    
} // ecs

#define DEFINE_ENTITY_UPDATE_SYSTEM(SystemName, ...) \
class SystemName final : public ecs::IUpdateSystem<__VA_ARGS__> { \
using Super = ecs::IUpdateSystem<__VA_ARGS__>;\
public: \
void Update(const ecs::IEntityBase& entity, __VA_ARGS__) const override; \
};

#define DEFINE_ENTITY_DRAW_SYSTEM(SystemName, ...) \
class SystemName final : public ecs::IDrawSystem<__VA_ARGS__> { \
using Super = ecs::IDrawSystem<__VA_ARGS__>;\
public: \
void Draw(const ecs::IEntityBase& entity, __VA_ARGS__) const override; \
};