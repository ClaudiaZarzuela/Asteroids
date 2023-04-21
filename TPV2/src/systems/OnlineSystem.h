#pragma once
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include <string>
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

	OnlineSystem() {}
	~OnlineSystem();
private:
	void activateSystem();
	void deactivateSystem();
	void error();
	Uint8 state_ = 0; // El estado actual del juego (en lugar del componente State);
	bool active_ = false;

	void initHost();
	void initClient();

	SDLNet_SocketSet set;
	TCPsocket masterSocket = nullptr;
	TCPsocket client = nullptr;
	TCPsocket hostSocket = nullptr;
	TCPsocket conn = nullptr;

	int port = 4444;
	std::string host;
	char buffer[256];
	int result = 0;


	int currentType;
	int currentState = NONE;
	enum typeMode{HOST_, CLIENT_};
	enum state{NONE, WAITING, START};
};

