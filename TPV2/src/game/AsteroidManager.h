#pragma once
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "ecs_def.h"

class AsteroidManager
{
private: 
	Manager* mngr_;
	int currAsteroids;
	float elapsedTime = sdlutils().currRealTime();
public:
	AsteroidManager() : mngr_(Manager::instance()), currAsteroids(0) {}
	void createAsteroids(int numAst);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	void onCollision(Entity* a);
	void Divide(Entity* a);
};

