#pragma once
#include "../checkML.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

// componente encargado de generar y disparar una bala 
struct Gun : public Component
{
public:
	// id
	constexpr static ecs::cmpId_type id = ecs::_GUN;
	// metodos publicos de la clase
	Gun(Texture* tex) : tr_(nullptr), tex_(tex) {};
	virtual ~Gun();
	void initComponent() override;
	void instanciateBullet();
	InputHandler* input_ = InputHandler::instance();

private:
	Texture* tex_;
	Transform* tr_;
};

