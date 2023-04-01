#pragma once
#include "../checkML.h"
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"

class AsteroidsSystem : public System {
public:
	constexpr static ecs::sysId_type id = ecs::_sys_ASTEROIDS;
	AsteroidsSystem(){};
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	virtual void recieve(const ecs::Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override{};
	// Si el juego est� parado no hacer nada, en otro caso mover los asteroides como
	// en la pr�ctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
	// de los 10 al principio de cada ronda).
	void update() override;
	virtual ~AsteroidsSystem() { }
private:
	float elapsedTime = sdlutils().currRealTime();
	//desactiva el asteroide con el que ha chocado la nave
	void FighterCrashed(Entity* a);
	// Destruye todos los asteroides
	void destroyAllAsteroids();
	// A�ade un asteroide cada 5 secs
	void addAsteroidFrequently();
	// a�ade el numero de asteroides especificado
	void addStar(unsigned int n);
	// Para gestionar el mensaje de que ha habido un choque de un asteroide con una
	// bala. Desactivar el asteroide �a� y crear 2 asteroides como en la pr�ctica 1,
	// y si no hay m�s asteroides enviar un mensaje correspondiente.
	void onCollision_AsteroidBullet(Entity* a);
	// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todos los
	// asteroides, y desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema y
	// a�adir los asteroides iniciales (como en la pr�ctica 1).
	void onRoundStart();
	// El n�mero actual de asteroides en el juego (recuerda que no puede superar un
	// l�mite)
	Uint8 numOfAsteroids_ = 0;
	// Indica si el sistema est� activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no est� activo)
	bool active_  = false;
};