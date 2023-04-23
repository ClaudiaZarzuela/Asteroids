#pragma once
#include "../checkML.h"
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"

class FighterSystem : public System {
public:
	constexpr static ecs::sysId_type id = ecs::_sys_FIGHTER;
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void recieve(const ecs::Message& m) override;
	// Crear la entidad del caza, a�adir sus componentes, asociarla con un handler
	// correspondiente, etc.
	void initSystem() override;
	// Si el juego est� parado no hacer nada, en otro caso actualizar la velocidad
	// del caza y moverlo como en la pr�ctica 1 (acelerar, desacelerar, etc). Adem�s, 
	// si el juego no est� parado y el jugador pulsa la tecla de disparo, enviar un
	// mensaje con las caracter�sticas f�sicas de la bala. Recuerda que se puede disparar
	// s�lo una bala cada 0.25sec.
	void update() override;
private:
	bool online = false;
	void createPlayer();
	void initializePlayers(int player);
	bool hasShot = false;

	InputHandler* input_ = InputHandler::instance();
	bool shoot = true;
	float elapsedTime = 0;
	Vector2D newVel = { 0, 0 };
	Transform* tr_ = nullptr;
	Transform* enemyTr_ = nullptr;
	void updateEnemy(int x_, int y_, int rot_, Vector2D vel_, bool bullet_);

	// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotaci�n 0. No
	// hace falta desactivar la entidad (no dibujarla si el juego est� parado).
	void onCollision_FighterAsteroid();
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();
	// Indica si el sistema est� activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no est� activo)
	bool active_ = false;
	// Resetea el numero de vidas del caza
	void resetLives();

	void playerShot(Entity* e);
};

