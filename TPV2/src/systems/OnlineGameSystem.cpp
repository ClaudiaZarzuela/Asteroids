#include "OnlineGameSystem.h"
#include "../checkML.h"

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void OnlineGameSystem::recieve(const ecs::Message& m) {
	switch (m.id) {
		case ecs::_m_START_ONLINE_ROUND: std::cout << "Empezar partida" << std::endl; break;
	}
}

// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado como en la práctica 1, etc. Tiene que enviar mensajes correspondientes cuando
// empieza una ronda o cuando empieza una nueva partida.
void OnlineGameSystem::update() {
	if (active_) {
		
		
	}
}