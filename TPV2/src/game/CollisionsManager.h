#pragma once
#include "../checkML.h"
#include "../ecs/Manager.h"
#include "AsteroidManager.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"

class PlayState;
class CollisionsManager
{
private:
	Manager* mngr_;
	AsteroidManager* aMngr_;
	PlayState* playState_;
public:

	CollisionsManager(AsteroidManager* aMngr, Manager* m, PlayState* playState) : mngr_(m), aMngr_(aMngr), playState_(playState) {}
	void checkCollision();
};


