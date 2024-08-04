//
// Created by elito on 7/27/2024.
//

#pragma once
#include "../ECSConstants.h"

namespace ecs::component {

/// Base abstract class for components
// All components should derive from this class
    struct IEntityComponent {

        IEntityComponent() = default;

        explicit IEntityComponent(bool ShouldStartActive) : bIsActive(ShouldStartActive) {};

        virtual ~IEntityComponent() = default;

        [[nodiscard]] constexpr virtual EntityComponentType GetType() const = 0;

        bool bIsActive = true;
    };

} // ecs component

/******************
 * INTERNAL MACROS - NOT FOR EXTERNAL USE
 ******************/
// dumb macro that we need to pass commas to another macros param without it thinking that it's a new param
#define COMMA ,

/*
 * Class declarations and flow
 * The basic information required from a component class to function
 */

/// Base macro to start defining a component
#define INTERNAL_COMPONENT_BASE_DECLARATION(ComponentName) \
    struct ComponentName : public ecs::component::IEntityComponent {                           \
    private:                                                   \
        using Super = ecs::component::IEntityComponent;                                            \
    public:                                                \
        [[nodiscard]] constexpr ecs::EntityComponentType GetType() const override { return ComponentName::GetComponentType(); }\
        [[nodiscard]] static constexpr ecs::EntityComponentType GetComponentType() { return #ComponentName; }\

/// Define a property in a component with get/set props configured
#define INTERNAL_COMPONENT_PROPERTY_DECLARATION(ParamType, ParamName) \
    private:                                                   \
        ParamType ParamName;                                       \
                                                               \
    public:                                                    \
        const ParamType Get##ParamName() const { return ParamName; }\
        void Set##ParamName(ParamType NewValue) { ParamName = NewValue; }\

/// End of component definition
#define INTERNAL_COMPONENT_END_DECLARATION() \
    };

/*
 * Constructor definition macros to allow creating default initialization constructors that support parameters
 */
// Constructor parameters
#define INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_DECLARATION(ParamType, ParamName) ParamType ParamName##Input

// Field constructor call
#define INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER(ParamType, ParamName) ParamName(ParamName##Input)

#define INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER_RAW(ParamName) ParamName()

// Constructor generation
#define INTERNAL_COMPONENT_CONSTRUCTOR_DECLARATION(ComponentName, ParameterDeclarations, ParameterInitializers, RawInitializers) \
    public:                                                         \
        ComponentName() : Super(),                                  \
            RawInitializers {};                       \
                                                                    \
        explicit ComponentName(ParameterDeclarations) : Super(),      \
            ParameterInitializers {};\

/******************
* PUBLIC MACROS FOR DEFINING USER COMPONENTS
 * Usage example:
 *
 * DEFINE_COMPONENT_TWO_PARAMETER(TransformComponent, int, X, int Y)
 * Will generate a component named TransformComponent with an X and a Y param.
******************/

// This was a terrible idea, send help
#define DEFINE_COMPONENT(ComponentName) \
    INTERNAL_COMPONENT_BASE_DECLARATION(ComponentName)                                              \
    INTERNAL_COMPONENT_END_DECLARATION()

#define DEFINE_COMPONENT_ONE_PARAMETER(ComponentName, ParamType, ParamName) \
    INTERNAL_COMPONENT_BASE_DECLARATION(ComponentName)                                              \
        INTERNAL_COMPONENT_CONSTRUCTOR_DECLARATION(ComponentName,                                   \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_DECLARATION(ParamType, ParamName),              \
                                                                                                    \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER(ParamType, ParamName),             \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER_RAW(ParamName))         \
        INTERNAL_COMPONENT_PROPERTY_DECLARATION(ParamType, ParamName)                               \
    INTERNAL_COMPONENT_END_DECLARATION()

#define DEFINE_COMPONENT_TWO_PARAMETER(ComponentName, ParamType, ParamName, ParamType2, ParamName2) \
    INTERNAL_COMPONENT_BASE_DECLARATION(ComponentName)                                              \
        INTERNAL_COMPONENT_CONSTRUCTOR_DECLARATION(ComponentName,                                   \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_DECLARATION(ParamType, ParamName)COMMA            \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_DECLARATION(ParamType2, ParamName2),           \
                                                                                                    \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER(ParamType, ParamName)COMMA         \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER(ParamType2, ParamName2),           \
            \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER_RAW(ParamName)COMMA                \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER_RAW(ParamName2))           \
        INTERNAL_COMPONENT_PROPERTY_DECLARATION(ParamType, ParamName)                               \
        INTERNAL_COMPONENT_PROPERTY_DECLARATION(ParamType2, ParamName2)       \
    INTERNAL_COMPONENT_END_DECLARATION()

#define DEFINE_COMPONENT_THREE_PARAMETER(ComponentName, ParamType, ParamName, ParamType2, ParamName2, ParamType3, ParamName3) \
    INTERNAL_COMPONENT_BASE_DECLARATION(ComponentName)                                              \
        INTERNAL_COMPONENT_CONSTRUCTOR_DECLARATION(ComponentName,                                   \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_DECLARATION(ParamType, ParamName)COMMA            \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_DECLARATION(ParamType2, ParamName2)COMMA         \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_DECLARATION(ParamType3, ParamName3),\
                                                                                                    \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER(ParamType, ParamName)COMMA         \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER(ParamType2, ParamName2)COMMA         \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER(ParamType3, ParamName3),                                     \
            \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER_RAW(ParamName)COMMA                \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER_RAW(ParamName2)COMMA                                         \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER_RAW(ParamName3))\
        INTERNAL_COMPONENT_PROPERTY_DECLARATION(ParamType, ParamName)                               \
        INTERNAL_COMPONENT_PROPERTY_DECLARATION(ParamType2, ParamName2)                               \
        INTERNAL_COMPONENT_PROPERTY_DECLARATION(ParamType3, ParamName3)\
    INTERNAL_COMPONENT_END_DECLARATION()

#define DEFINE_COMPONENT_FOUR_PARAMETER(ComponentName, \
    ParamType, ParamName, \
    ParamType2, ParamName2, \
    ParamType3, ParamName3, \
    ParamType4, ParamName4)                             \
    \
    INTERNAL_COMPONENT_BASE_DECLARATION(ComponentName)                                              \
        INTERNAL_COMPONENT_CONSTRUCTOR_DECLARATION(ComponentName,                                   \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_DECLARATION(ParamType, ParamName)COMMA            \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_DECLARATION(ParamType2, ParamName2)COMMA         \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_DECLARATION(ParamType3, ParamName3)COMMA       \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_DECLARATION(ParamType4, ParamName4),\
                                                                                                    \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER(ParamType, ParamName)COMMA         \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER(ParamType2, ParamName2)COMMA         \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER(ParamType3, ParamName3)COMMA       \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER(ParamType4, ParamName4),           \
                                                       \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER_RAW(ParamName)COMMA                \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER_RAW(ParamName2)COMMA                   \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER_RAW(ParamName3)COMMA                \
            INTERNAL_COMPONENT_CONSTRUCTOR_PARAMETER_INITIALIZER_RAW(ParamName4)))\
        INTERNAL_COMPONENT_PROPERTY_DECLARATION(ParamType, ParamName)                               \
        INTERNAL_COMPONENT_PROPERTY_DECLARATION(ParamType2, ParamName2)                               \
        INTERNAL_COMPONENT_PROPERTY_DECLARATION(ParamType3, ParamName3)                             \
        INTERNAL_COMPONENT_PROPERTY_DECLARATION(ParamType4, ParamName4)\
    INTERNAL_COMPONENT_END_DECLARATION()
