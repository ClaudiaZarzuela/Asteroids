#pragma once
#include "../checkML.h"
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Button.h"

class ButtonSystem : public System
{
public:
	constexpr static ecs::sysId_type id = ecs::_sys_BUTTON;
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void recieve(const ecs::Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego está parado no hacer nada, en otro caso comprobar colisiones como
	// en la práctica 1 y enviar mensajes correspondientes.
	void update() override;

private:
	bool active_ = true;
	bool clicked = false;
	enum button_ID { MULTIPLAYER_ = 0, SINGLEPLAYER_ = 1, HOST_ = 2, CLIENT_ = 3 };
	void createMainMenuButtons();
	void createOnlineStateButtons();
	void activateSystem();
	void deactivateSystem();
	void erasePreviousButtons();
};