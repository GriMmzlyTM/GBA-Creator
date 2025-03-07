#pragma once
#include <memory>
#include <vector>

#include "ISystem.h"
#include "ECSConstants.h"
#include "World.h"

namespace ecs {
    class SystemManager : public WorldObject {
    public:

        template<IsEntitySystem TSystem>
        void AddDrawSystem() {
            m_drawSystems.push_back(std::make_unique<TSystem>());
        }

        template<IsEntitySystem TSystem>
        void AddUpdateSystem() {
            m_updateSystems.push_back(std::make_unique<TSystem>());
        }

        void ExecuteDraw(const IEntityBase& entity) const;
        void ExecuteUpdate(const IEntityBase& entity) const;

    private:
        std::vector<std::unique_ptr<ISystem>> m_updateSystems;
        std::vector<std::unique_ptr<ISystem>> m_drawSystems;
    };
}
