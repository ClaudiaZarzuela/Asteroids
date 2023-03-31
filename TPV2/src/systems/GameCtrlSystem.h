#pragma once
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"

class GameCtrlSystem : public System {
public:
	constexpr static ecs::sysId_type id = ecs::_sys_CNTRL;
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void recieve(const ecs::Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
	// como en la práctica 1, etc. Tiene que enviar mensajes correspondientes cuando
	// empieza una ronda o cuando empieza una nueva partida.
	void update() override;
private:
	// Para gestionar el mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
	// al fighter, y si no hay más vidas avisar que ha acabado el juego (y quien
	// es el ganador).
	void onCollision_FighterAsteroid();
	// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
	// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
	void onAsteroidsExtinction();
	Uint8 score_;
	Uint8 winner_; // 0 - None, 1 - Asteroids, 2- Fighter
	Uint8 state_; // El estado actual del juego (en lugar del componente State);

	InputHandler* input_ = InputHandler::instance();
	bool shoot = true;
	float elapsedTime = 0;
};