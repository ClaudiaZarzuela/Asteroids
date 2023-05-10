#pragma once
#include <SDL_net.h>
#include "../checkML.h"
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"
class InputTextSystem : public System {
public:
	constexpr static ecs::sysId_type id = ecs::_sys_TEXTINPUT;
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void recieve(const ecs::Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override{};
	// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
	// como en la práctica 1, etc. Tiene que enviar mensajes correspondientes cuando
	// empieza una ronda o cuando empieza una nueva partida.
	void update() override;
	InputTextSystem(){}
	~InputTextSystem(){}
private:
	bool active_ = true;
	void activateSystem();
	void deactivateSystem();
	std::vector<std::string> strSplit(std::string s, char c);
	InputHandler* input_ = InputHandler::instance();
	SDL_Event event = input_->getCurrentEvent();
	std::string str = "";
	int sizetext = 0;
};


