#pragma once
#include <SDL_net.h>
#include "../checkML.h"
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
	bool gameEnded = false; //booleano que permite usar el input despues de que haya finalizado la partida para pasar de estado
	void initHost(); //inicializacion tcp del host
	void initClient(); //inicializacion tcp del client
	void descifraMsg( char* buffer); //metodo al que se llama para descifrar el mensaje online que se ha recibido desde el otro ordenador
	void informOfMovement(float x, float y, float rot, Vector2D vel, bool bullet); //informa sobre la posicion de tu nave al otro jugador online mediante mensaje
	void informOfCollision(int playerWinner); //informa sobre si ha colisionado tu nave al otro jugador online mediante mensaje
	void moveOponent(float x, float y, float r); //recive el mensaje que actualiza la posicion de la nave enemiga en tu ordenador
	void shoot(Vector2D pos, Vector2D vel, double width, double height, double rot);  //informa sobre si has disparado al otro jugador online mediante mensaje
	void resetConnection(); // cuando se va el cliente resetea todo lo necesario de tcp para poder crear una nueva conexion sin problemas con otro cliente nuevo
	void resetOnline();//cuando se va el host resetea todo lo necesario de tcp para poder empezar una partida online desde cero

	std::vector<std::string> strSplit(std::string s, char c); //separa un mensaje de tipo string a un vector de palabras
	SDLNet_SocketSet set = nullptr;
	TCPsocket masterSocket = nullptr;
	TCPsocket conn = nullptr;

	InputHandler* input_ = InputHandler::instance();
	int port = 4444;
	std::string host; //ip del host
	char buffer[256];
	int result = 0;

	int currentType; //si eres host o client
	std::string nameHost = "Name ";
	std::string nameClient = "Name ";
	Transform* trOponent = nullptr;
	enum typeMode{NONE_, HOST_, CLIENT_}; 
};

//EXCEPCIONES PERSONALIZADAS
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