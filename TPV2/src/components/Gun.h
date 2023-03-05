#pragma once
#include "../checkML.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

class Gun : public Component
{
public: 
	constexpr static ecs::cmpId_type id = ecs::_GUN;
	Gun(Texture* tex) : tex_(tex) {};
	virtual ~Gun();
	void initComponent() override;
	void instanciateBullet();
	InputHandler* input_ = InputHandler::instance();

private:
	Texture* tex_;
	Transform* tr_;
};

