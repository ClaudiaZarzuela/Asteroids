#pragma once
#include "../ecs/Manager.h"
#include "AsteroidManager.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"

class CollisionsManager
{
private:
	Manager* manager_;
	AsteroidManager* aManager;
public:

	CollisionsManager(AsteroidManager* aMngr, Manager* m) : manager_(m), aManager(aMngr){}
	void checkCollision();
};


