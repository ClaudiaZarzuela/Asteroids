#pragma once
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
class Generations : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_GENERATIONS;
	Generations(){}
};

