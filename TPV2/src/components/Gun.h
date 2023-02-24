#pragma once
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

class Gun : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_GUN;
	Gun(Texture* tex) :
		tr_(nullptr),
		tex_(tex) {
	}
	virtual ~Gun();
	void initComponent() override;
	void update() override;

private:
	Transform* tr_;
	Texture* tex_;
	InputHandler* input_ = InputHandler::instance();
};

