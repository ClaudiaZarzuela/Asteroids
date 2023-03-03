#include "CollisionsManager.h"
#include "ecs_def.h"
#include "../components/Transform.h"

// no se desde donde llamar a este pingo
void /*bool*/ CollisionsManager::checkCollisison() {
	bool collision = false;
	
	auto nave = mngr_->getHandler(ecs::FIGHTER)->getComponent<Transform>();
	for (auto it = mngr_->getEntitiesByGroup(ecs::_grp_ASTEROIDS).begin(); it != mngr_->getEntitiesByGroup(ecs::_grp_ASTEROIDS).end(); ++it) {

		auto asteroide = (*it)->getComponent<Transform>();

		cout << (*it)->isAlive() << endl;
		if ((*it)->isAlive()) {

			if (Collisions::collidesWithRotation(nave->getPos(), nave->getW(), nave->getH(), nave->getRot(), asteroide->getPos(), asteroide->getW(), asteroide->getH(), asteroide->getRot())) {
				
				aMngr_->onCollision((*it));
				//(*it)->setAlive(false);
				//aMngr_->destroyAllAsteroids();
				/*
				desactiva todas las balas, 
				quita una vida al caza, 
				marca el juego como PAUSED o GAMEOVER (depende de si quedan vidas)
				y pon al caza en el centro de la ventana con velocidad cero y rotación cero.
				*/
				collision = true;
				return; 
			}
		
			for (auto ot = mngr_->getEntitiesByGroup(ecs::_grp_BULLETS).begin(); ot != mngr_->getEntitiesByGroup(ecs::_grp_BULLETS).end(); ++ot) {
				auto bala = (*ot)->getComponent<Transform>();
				if (Collisions::collidesWithRotation(bala->getPos(), bala->getW(), bala->getH(), bala->getRot(), asteroide->getPos(), asteroide->getW(), asteroide->getH(), asteroide->getRot())) {
					cout << "chocaste bala y asteroide" << endl;
					//(*ot)->setAlive(false);
					aMngr_->onCollision((*it));
					/*Si no hay más asteroides, gana el caza.*/
					collision = true;
					return;
				}
			}	
		}
	}
//	return collision;
}