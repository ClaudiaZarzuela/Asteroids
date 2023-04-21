#pragma once
#include "../checkML.h"
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"

class OnlineGameSystem : public System {
public:
	constexpr static ecs::sysId_type id = ecs::_sys_CNTRL;
	void recieve(const ecs::Message& m) override;
	void initSystem() override { };
	void update() override;
private:
	
	Uint8 score_;
	Uint8 winner_; // 0 - None, 1 - Asteroids, 2- Fighter
	Uint8 state_ = 0; // El estado actual del juego (en lugar del componente State);
	InputHandler* input_ = InputHandler::instance();
	bool active_ = false;

};