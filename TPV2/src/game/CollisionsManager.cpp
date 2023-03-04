#include "CollisionsManager.h"
#include "ecs_def.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../../states/PauseState.h"
#include "Game.h"
#include "../../states/PlayState.h"
// no se desde donde llamar a este pingo
void CollisionsManager::checkCollision() {
	vector<Entity*> ast = mngr_->getEntities(ecs::_grp_ASTEROIDS);
	vector<Entity*> bull = mngr_->getEntities(ecs::_grp_BULLETS);

	auto playerTransform = mngr_->getHandler(ecs::FIGHTER)->getComponent<Transform>();
	auto player = mngr_->getHandler(ecs::FIGHTER);

	for (int i = 0; i < ast.size(); ++i) {
		auto asteroide = ast[i]->getComponent<Transform>();
		if (Collisions::collidesWithRotation(playerTransform->getPos(), playerTransform->getW(), playerTransform->getH(), playerTransform->getRot(),
			asteroide->getPos(), asteroide->getW(), asteroide->getH(), asteroide->getRot())) {
			//aMngr_->destroyAllAsteroids();
			player->getComponent<Health>()->loseLife();
			for (auto b : bull) b->setAlive(false);
			playerTransform->reset();
			if (player->getComponent<Health>()->getLives() <= 0) {
				//gameover
			}
			else { // HACER OTRO ESTADO PARA ESTA PINGA QUE SEA DISTINTO AL DE PAUSA
				playState_->changeState();
				//aMngr_->createAsteroids(10);
			}
			break;
		}
		for (auto ot = mngr_->getEntities(ecs::_grp_BULLETS).begin(); ot != mngr_->getEntities(ecs::_grp_BULLETS).end(); ++ot) {
			auto bala = (*ot)->getComponent<Transform>();
			if (Collisions::collidesWithRotation(bala->getPos(), bala->getW(), bala->getH(), bala->getRot(), 
				asteroide->getPos(), asteroide->getW(), asteroide->getH(), asteroide->getRot())) {
				(*ot)->setAlive(false);
				aMngr_->onCollision((ast[i]));
				break;
			}
		}	
	}
}