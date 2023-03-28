#pragma once
#include "../checkML.h"
#include "Transform.h"
#include "Gun.h"
#include "../sdlutils/InputHandler.h"

// componente que se encarga de la recogida del input de la nave
struct FighterCtrl: public Component
{
public:
	// id
	constexpr static ecs::cmpId_type id = ecs::_CTRL;
	// metodos publicos de la clase
	FighterCtrl() : tr_(nullptr), gn_(nullptr) {};
	virtual ~FighterCtrl();
	void initComponent() override;
	//void handleInput() override;
	InputHandler* input_ = InputHandler::instance();
private:
	Transform* tr_;
	Gun* gn_;
	bool shoot = true;
	float elapsedTime = 0;
};

