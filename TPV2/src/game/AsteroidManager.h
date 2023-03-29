#pragma once
#include "../checkML.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "ecs_def.h"

// clase encargada de gestonar los asteroides, su creacion, destruccion y colisiones
class AsteroidManager
{
private: 
	Manager* mngr_;
	int currAsteroids;
	float elapsedTime = sdlutils().currRealTime();
public:
	// metodos publicos de la clase
	AsteroidManager(Manager* m) : mngr_(m), currAsteroids(0) {}
	virtual void update();
	void createAsteroids(int numAst);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	void onCollision(Entity* a);
	void Divide(Entity* a);
};

