#pragma once
#include "Transform.h"
#include "../sdlutils/InputHandler.h"
class FighterCtrl: public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_CTRL;
	FighterCtrl() {};
	virtual ~FighterCtrl();
	void initComponent() override;
	void update() override;
	InputHandler* input_ = InputHandler::instance();
private:
	Transform* tr_;
};

