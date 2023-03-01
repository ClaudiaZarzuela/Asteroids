#pragma once
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
class Generations : public Component
{
private:
	int generation = 0;

public:
	constexpr static ecs::cmpId_type id = ecs::_GENERATIONS;
	Generations(int gen) : generation(gen) {}
	int getGeneration() { return generation; }
	int setGeneration(int newGen) { generation = newGen; }
};

