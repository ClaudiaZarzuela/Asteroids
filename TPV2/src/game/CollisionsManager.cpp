#include "CollisionsManager.h"
#include "ecs_def.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "Game.h"
#include "../../states/PlayState.h"
#include "../checkML.h"
#include "../../states/GameOverState.h"
#include "../sdlutils/SDLUtils.h"

// metodo encargado de comprpbar las colisiones de los asteroides con el caza y con las balas, y aplicar los efectos correspondientes de darse estas
void CollisionsManager::checkCollision() {/*
	vector<Entity*> ast = mngr_->getEntities(ecs::_grp_ASTEROIDS);
	vector<Entity*> bull = mngr_->getEntities(ecs::_grp_BULLETS);

	auto playerTransform = mngr_->getHandler(ecs::FIGHTER)->getComponent<Transform>();
	auto player = mngr_->getHandler(ecs::FIGHTER);

	for (int i = 0; i < ast.size(); ++i) {
		auto asteroide = ast[i]->getComponent<Transform>();
		if (Collisions::collidesWithRotation(playerTransform->getPos(), playerTransform->getW(), playerTransform->getH(), playerTransform->getRot(),
			asteroide->getPos(), asteroide->getW(), asteroide->getH(), asteroide->getRot())) {
			
			ifCollision();
			
			if (player->getComponent<Health>()->getLives() <= 0) {
				playState_->callGameOver("Lose");
			}
			else { playState_->changeState();}
			break;
		}
		for (auto ot = mngr_->getEntities(ecs::_grp_BULLETS).begin(); ot != mngr_->getEntities(ecs::_grp_BULLETS).end(); ++ot) {
			auto bala = (*ot)->getComponent<Transform>();
			if (Collisions::collidesWithRotation(bala->getPos(), bala->getW(), bala->getH(), bala->getRot(), 
				asteroide->getPos(), asteroide->getW(), asteroide->getH(), asteroide->getRot())) {
				sdlutils().soundEffects().at("gunshot").play();
				(*ot)->setAlive(false);
				aMngr_->onCollision((ast[i]));
				break;
			}
		}	
	}*/
}

void CollisionsManager::ifCollision() {/*
	auto player = mngr_->getHandler(ecs::FIGHTER);
	sdlutils().soundEffects().at("explosion").play();
	player->getComponent<Health>()->loseLife();
	for (auto b : mngr_->getEntities(ecs::_grp_BULLETS)) b->setAlive(false);
	player->getComponent<Transform>()->reset();
	aMngr_->destroyAllAsteroids();*/
}