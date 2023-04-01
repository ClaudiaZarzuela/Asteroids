#pragma once
#include "../checkML.h"
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"

class AsteroidsSystem : public System {
public:
	constexpr static ecs::sysId_type id = ecs::_sys_ASTEROIDS;
	AsteroidsSystem(){};
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	virtual void recieve(const ecs::Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override{};
	// Si el juego está parado no hacer nada, en otro caso mover los asteroides como
	// en la práctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
	// de los 10 al principio de cada ronda).
	void update() override;
	virtual ~AsteroidsSystem() { }
private:
	float elapsedTime = sdlutils().currRealTime();
	// Destruye todos los asteroides
	void destroyAllAsteroids();
	// Añade un asteroide cada 5 secs
	void addAsteroidFrequently();
	// añade el numero de asteroides especificado
	void addStar(unsigned int n);
	// Para gestionar el mensaje de que ha habido un choque de un asteroide con una
	// bala. Desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1,
	// y si no hay más asteroides enviar un mensaje correspondiente.
	void onCollision_AsteroidBullet(Entity* a);
	// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todos los
	// asteroides, y desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema y
	// añadir los asteroides iniciales (como en la práctica 1).
	void onRoundStart();
	// El número actual de asteroides en el juego (recuerda que no puede superar un
	// límite)
	Uint8 numOfAsteroids_ = 0;
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_;
};