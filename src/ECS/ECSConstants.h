//
// Created by elito on 7/24/2024.
//

#pragma once
#include <cstdint>

namespace ecs {

    class ISystem;
    class IUpdateSystem;
    class IDrawSystem;

    // Components
    typedef const char *EntityComponentType;

    /// Constraint for IEntityComponent generics
    /// \tparam T Passed type that is expected to be a component
    template<typename T>
    concept IsEntityComponent = requires(T component) {
        T::GetComponentType();
        component.GetType();
        component.bIsActive;
    };

    // Entities
    typedef const int32_t EntityID;
    typedef const char* EntityName;

    template<typename T>
    concept IsEntity = requires(T entity) {
        entity.Name;
        entity.Identifier;
    };

    template<typename TSystem>
    concept IsEntitySystem = requires(TSystem system)
    {
        TSystem::IsActive;
        TSystem::ProcessEntity;
    };
    
}
