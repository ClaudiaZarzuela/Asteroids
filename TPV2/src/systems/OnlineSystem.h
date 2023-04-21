#pragma once
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include <SDL_net.h>

class OnlineSystem : public System {
public:
	constexpr static ecs::sysId_type id = ecs::_sys_ONLINE;
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void recieve(const ecs::Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
	// como en la práctica 1, etc. Tiene que enviar mensajes correspondientes cuando
	// empieza una ronda o cuando empieza una nueva partida.
	void update() override;

private:
	void activateSystem();
	void deactivateSystem();
	void error();
	Uint8 state_ = 0; // El estado actual del juego (en lugar del componente State);
	bool active_ = false;

	void initHost();
	void initClient();

	SDLNet_SocketSet set;
	TCPsocket masterSocket;
	TCPsocket client;
	TCPsocket hostSocket;
	TCPsocket conn;

	int port = 4444;
	char* host = 0;
	char buffer[256];
	int result = 0;


	int currentType;
	enum typeMode{HOST_, CLIENT_};
};

