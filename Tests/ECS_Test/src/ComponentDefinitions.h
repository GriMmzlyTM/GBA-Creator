#pragma once

#include "IEntityComponent.h"

DEFINE_COMPONENT(RenderComponent)
DEFINE_COMPONENT(PlayerComponent)
DEFINE_COMPONENT_TWO_PARAMETER(TransformComponent, int, X, int, Y)