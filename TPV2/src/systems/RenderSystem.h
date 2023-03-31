#pragma once
#include "../ecs/System.h"
#include "../ecs/Manager.h"

class RenderSystem : public System {
//public:
//	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
//	void recieve(const ecs::Message& m) override;
//	// Inicializar el sistema, etc.
//	void initSystem() override;
//	// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
//	// - Dibujar las vidas (siempre).
//	// - Dibujar los mensajes correspondientes: si el juego está parado, etc (como en
//	// la práctica 1)
//	void update() override;
//private:
//	// Para gestionar los mensajes correspondientes y actualizar los atributos
//	// winner_ y state_. 
//	void onRoundStart();
//	void onRoundOver();
//	void onGameStart();
//	void onGameOver();
//	Uint8 winner_; // 0 - None, 1 - Asteroid, 2- Fighter
//	Uint8 state_; // El estado actual de juego (como en GameCtrlSystem)
};