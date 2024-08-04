#pragma once
#include "../Systems/SystemManager.h"
#include "../Entities/EntityManager.h"

namespace ecs {
    class World {

        std::unique_ptr<Entity::EntityManager> m_entityManager;
        std::unique_ptr<System::SystemManager> m_systemManager;
        
    public:

        World();
        ~World() = default;
        
        void ExecuteWorld() const;
        std::weak_ptr<Entity::IEntityBase> GetEntity(EntityID entityID) const;
    };
}
