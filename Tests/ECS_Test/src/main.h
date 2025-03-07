#pragma once
#include "IEntityComponent.h"
#include "ISystem.h"

DEFINE_COMPONENT(TestRenderComponent)
DEFINE_COMPONENT_TWO_PARAMETER(TestTransformComponent, int, x, int, y)
DEFINE_COMPONENT(TestPlayerComponent)

DEFINE_ENTITY_DRAW_SYSTEM(RenderSystem, TestRenderComponent, TestTransformComponent)
DEFINE_ENTITY_UPDATE_SYSTEM(MoveSystem, TestPlayerComponent, TestTransformComponent)
