#pragma once
#include "../ecs/Manager.h"
#include "AsteroidManager.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"

class CollisionsManager
{
private:
	Manager* mngr_;
	AsteroidManager* aMngr_;
public:

	CollisionsManager(AsteroidManager* aMngr, Manager* m) : mngr_(m), aMngr_(aMngr){}
	void checkCollision();
};


