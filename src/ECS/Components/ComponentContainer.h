//
// Created by elito on 7/24/2024.
//

#pragma once

#include <vector>
#include <queue>
#include "IEntityComponent.h"
#include "../ECSConstants.h"
#include "../Entities/Entity.h"
#include <map>

namespace ecs::component {

    class IComponentContainer {
    public:
        [[nodiscard]] virtual EntityComponentType GetSupportedComponentType() const = 0;

        IComponentContainer() = default;
    };

    ///
    /// \tparam TComponent
    template<IsEntityComponent TComponent>
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

        explicit ComponentContainer(const std::vector<Entity::IEntityBase> &EntityDefinitions);

        ///
        /// \param Id
        /// \return
        [[nodiscard]] TComponent GetComponent(EntityID Id) const;

        ///
        /// \return
        [[nodiscard]] EntityComponentType GetSupportedComponentType() const override {
            return TComponent::GetComponentType();
        }

        ///
        /// \param entityId
        /// \param component
        void UpdateComponent(EntityID entityId, TComponent &component);
    };

    template<IsEntityComponent TComponent>
    ComponentContainer<TComponent>::ComponentContainer(const std::vector<Entity::IEntityBase> &EntityDefinitions) {
        for (const Entity::IEntityBase entity : EntityDefinitions) {
            //TComponent componentToAdd = entity.
        }
    }

    /***
     * Template definitions
    */

    template<IsEntityComponent TComponent>
    void ComponentContainer<TComponent>::UpdateComponent(EntityID entityId, TComponent &component) {
        //TODO: Temporary, look into buffering
        assert(entityId < m_components->MAX_SIZE);
        m_components[entityId] = component;
    }

    template<IsEntityComponent TComponent>
    TComponent ComponentContainer<TComponent>::GetComponent(EntityID Id) const {
        const auto desiredComp = m_components->find(Id);
        if (desiredComp != m_components->end()) {
            return desiredComp->second;
        }
    }

} // ecs component


DEFINE_COMPONENT_ONE_PARAMETER(PositionComp, int, X)

using namespace ecs::component;

class Test {


    std::vector<IComponentContainer*> values;

    void MyFunc() {
        RenderComp renderComp;
        PositionComp positionComp(55);

        ComponentContainer<PositionComp> PositionContainer;

        ComponentContainer<RenderComp>* container = nullptr;
        if (GetComponentContainer<RenderComp>(container)) {

        }

    }

    template<ecs::IsEntityComponent TComponent>
    bool GetComponentContainer(ComponentContainer<TComponent>* OutContainer) {
        OutContainer = nullptr;
        for (auto* ComponentContainer : values) {
            auto* testContainer = static_cast<::ComponentContainer<TComponent>*>(ComponentContainer);
            if (testContainer != nullptr) {
                OutContainer = testContainer;
                return true;
            }
        }
        return false;
    }
};