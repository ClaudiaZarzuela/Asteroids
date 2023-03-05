#pragma once
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

class Gun : public Component
{
public: 
	/* pulsando S añade una bala al juego y reproduce el sonido fire.wav. Se 
	puede disparar sólo una bala cada 0.25sec (usar sdlutils().currTime()
	para consultar el tiempo actual).*/
	constexpr static ecs::cmpId_type id = ecs::_GUN;
	Gun(Texture* tex) : tex_(tex) {};
	virtual ~Gun();
	//void initComponent() override;
	void initComponent() override;
	void instanciateBullet();
	InputHandler* input_ = InputHandler::instance();

private:
	Texture* tex_;
	Transform* tr_;
	bool shoot = true;
	float elapsedTime = 0;

};

