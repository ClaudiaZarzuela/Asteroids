#pragma once
#include "../checkML.h"
#include "../ecs/Manager.h"
#include "AsteroidManager.h"
#include "../utils/Collisions.h"

//class PlayState;
// clase encargada de gestionar las colisiones de unas entidades con otras y sus efectos
class CollisionsManager
{
private:
	Manager* mngr_;
	AsteroidManager* aMngr_;
	//PlayState* playState_;
public:
	// metodos publicos de la clase
	CollisionsManager(AsteroidManager* aMngr, Manager* m) : mngr_(m), aMngr_(aMngr) {}
	void checkCollision();
	void ifCollision();
};


