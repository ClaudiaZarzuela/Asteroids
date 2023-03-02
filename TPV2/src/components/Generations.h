#pragma once
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
class Generations : public Component
{
private:
	int generation;

public:
	constexpr static ecs::cmpId_type id = ecs::_GENERATIONS;
	Generations() : generation(3) {}
	int getGeneration() { return generation; }
	int setGeneration(int newGen) { generation = newGen; }
};

