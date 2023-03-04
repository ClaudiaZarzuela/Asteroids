#pragma once
#include "../sdlutils/InputHandler.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
class StateInput : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_CTRL;
	StateInput() {};
	virtual ~StateInput(){};
	void update() override;
	InputHandler* input_ = InputHandler::instance();

};

