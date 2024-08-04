//
// Created by elito on 7/29/2024.
//

#pragma once

#include "../ECSConstants.h"
#include "../Entities/Entity.h"

namespace ecs::System {
    
    class ISystem {
    public:
        virtual ~ISystem() = default;

        void SetActive(bool bActive);
        [[nodiscard]] bool IsActive() const;

        void ProcessEntity(const std::weak_ptr<Entity::IEntityBase>& entity) const;
        
    protected:
        ISystem() = default;
        virtual void ProcessEntity_Internal(const std::weak_ptr<Entity::IEntityBase>& entityId) const = 0;

    protected:
        bool m_bIsActive = true;

    };

    /// System base
    /// @tparam TComponents 
    template<IsEntityComponent... TComponents>
    class SystemBase : public ISystem {

    protected:
        [[nodiscard]] constexpr bool EntityMatchesSystem(const std::weak_ptr<Entity::IEntityBase>& Entity) const {
            if (Entity.expired()) {
                // TODO: Error? Something?
                return false;
            }
            std::shared_ptr<Entity::IEntityBase> lockedEntity = Entity.lock();
            return (... && lockedEntity->HasComponent<TComponents>());
        }
    };

    /// Update System
    /// @tparam TComponents 
    template<IsEntityComponent... TComponents>
    class IUpdateSystem : public SystemBase<TComponents...> {
        using Super = SystemBase<TComponents...>;
    public:
        ~IUpdateSystem()  = default;
        virtual void Update(TComponents... Components) const = 0;

    protected:
        
        void ProcessEntity_Internal(const std::weak_ptr<Entity::IEntityBase>& Entity) const override {
            // We get all components once to check, this is probably very bad for performance
            if (!Super::EntityMatchesSystem(Entity)) {
                return;
            }

            std::shared_ptr<Entity::IEntityBase> lockedEntity = Entity.lock();
            Update(lockedEntity->GetComponent<TComponents>()...);
        }
    };

    /// Draw system
    /// @tparam TComponents 
    template<IsEntityComponent... TComponents>
    class IDrawSystem : public SystemBase<TComponents...> {
        using Super = SystemBase<TComponents...>;
    public:
        ~IDrawSystem() override = default;
        virtual void Draw(TComponents... Components) const = 0;

    protected:
        void ProcessEntity_Internal(const std::weak_ptr<Entity::IEntityBase>& Entity) const override {

            // We get all components once to check, this is probably very bad for performance
            if (!Super::EntityMatchesSystem(Entity)) {
                return;
            }
            std::shared_ptr<Entity::IEntityBase> lockedEntity = Entity.lock();
            Draw(lockedEntity->GetComponent<TComponents>()...);
        }
    };
    
} // ecs

#define DEFINE_ENTITY_UPDATE_SYSTEM(SystemName, ...) \
class SystemName final : public ecs::System::IUpdateSystem<__VA_ARGS__> { \
using Super = ecs::System::IUpdateSystem<__VA_ARGS__>;\
public: \
void Update(__VA_ARGS__) const override; \
};

#define DEFINE_ENTITY_DRAW_SYSTEM(SystemName, ...) \
class SystemName final : public ecs::System::IDrawSystem<__VA_ARGS__> { \
using Super = ecs::System::IDrawSystem<__VA_ARGS__>;\
public: \
void Draw(__VA_ARGS__) const override; \
};