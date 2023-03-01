#pragma once
#include "../ecs/Manager.h"
class AsteroidManager
{
private: 
	Manager* mngr_;
	int currAsteroids;
public:
	AsteroidManager() : mngr_(Manager::instance()), currAsteroids(0) {}
	void createAsteroids(int n);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	void onCollision(Entity* a);
	void update();
};

