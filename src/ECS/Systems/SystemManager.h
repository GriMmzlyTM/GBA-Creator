#pragma once
#include <memory>
#include <vector>

#include "ISystem.h"
#include "../ECSConstants.h"

namespace ecs::System {
DEFINE_COMPONENT(Test)
DEFINE_ENTITY_DRAW_SYSTEM(MySystem, Test)
DEFINE_ENTITY_UPDATE_SYSTEM(MyOtherSystem)
    class SystemManager {
    public:

        template<IsEntitySystem TSystem>
        void AddDrawSystem() {
            m_drawSystems.push_back(std::make_unique<TSystem>());
        }

        template<IsEntitySystem TSystem>
        void AddUpdateSystem() {
            m_updateSystems.push_back(std::make_unique<TSystem>());
        }

        void ExecuteDraw(const std::weak_ptr<Entity::IEntityBase>& entity) const;
        void ExecuteUpdate(const std::weak_ptr<Entity::IEntityBase>& entity) const;
        
    private:
        std::vector<std::unique_ptr<ISystem>> m_updateSystems;
        std::vector<std::unique_ptr<ISystem>> m_drawSystems;
    };
}
