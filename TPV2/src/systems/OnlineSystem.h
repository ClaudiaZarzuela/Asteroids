#pragma once
#include <SDL_net.h>
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"

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
	OnlineSystem();
	~OnlineSystem();
private:
	void activateSystem();
	void deactivateSystem();
	Uint8 state_ = 0; // El estado actual del juego (en lugar del componente State);
	bool active_ = false;
	bool gameEnded = false;
	void initHost();
	void initClient();
	void descifraMsg( char* buffer);
	void informOfMovement(float x, float y, float rot, Vector2D vel, bool bullet);
	void informOfCollision(int playerWinner);
	void moveOponent(float x, float y, float r);
	void shoot(Vector2D pos, Vector2D vel, double width, double height, double rot);
	void resetConnection();
	void resetOnline();

	std::vector<std::string> strSplit(std::string s, char c);
	SDLNet_SocketSet set = nullptr;
	TCPsocket masterSocket = nullptr;
	TCPsocket conn = nullptr;

	InputHandler* input_ = InputHandler::instance();
	int port = 4444;
	std::string host;
	char buffer[256];
	int result = 0;

	int currentType;
	int currentState = NONE;
	std::string nameHost = "Name ";
	std::string nameClient = "Name ";
	Transform* trOponent = nullptr;
	enum typeMode{NONE_, HOST_, CLIENT_};
	enum state{NONE, WAITING, START};
};

class client_lost : public std::exception {
public:
	std::string what() {
		return "Custom C++ Exception";
	}
};

class host_lost : public std::exception {
public:
	std::string what() {
		return "Custom C++ Exception";
	}
};