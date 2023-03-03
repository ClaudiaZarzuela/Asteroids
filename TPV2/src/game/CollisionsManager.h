#pragma once
#include "../ecs/Manager.h"
#include "AsteroidManager.h"
#include "../utils/Collisions.h"

class CollisionsManager
{
private:
	Manager* mngr_;
	AsteroidManager* aMngr_;
public:
	CollisionsManager(AsteroidManager* aMngr) : mngr_(Manager::instance()), aMngr_(aMngr){}
	void checkCollision();
};


