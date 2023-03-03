#include "CollisionsManager.h"
#include "ecs_def.h"
#include "../components/Transform.h"

// no se desde donde llamar a este pingo
void CollisionsManager::checkCollision() {
	vector<Entity*> ast = manager_->getEntities(ecs::_grp_ASTEROIDS);
	vector<Entity*> bull = manager_->getEntities(ecs::_grp_BULLETS);
	Entity* player = manager_->getHandler(ecs::FIGHTER);
	for (int i = 0; i < ast.size(); ++i) {
		if (Collisions::collidesWithRotation(player->getComponent<Transform>()->getPos(), player->getComponent<Transform>()->getW(), player->getComponent<Transform>()->getH(), player->getComponent<Transform>()->getRot(),
			ast[i]->getComponent<Transform>()->getPos(), ast[i]->getComponent<Transform>()->getW(), ast[i]->getComponent<Transform>()->getH(), ast[i]->getComponent<Transform>()->getRot())) {
			aManager->destroyAllAsteroids();
		}
		auto asteroide = ast[i]->getComponent<Transform>();
		for (auto ot = manager_->getEntities(ecs::_grp_BULLETS).begin(); ot != manager_->getEntities(ecs::_grp_BULLETS).end(); ++ot) {
			auto bala = (*ot)->getComponent<Transform>();
			if (Collisions::collidesWithRotation(bala->getPos(), bala->getW(), bala->getH(), bala->getRot(), asteroide->getPos(), asteroide->getW(), asteroide->getH(), asteroide->getRot())) {
				(*ot)->setAlive(false);
				aManager->onCollision((ast[i]));
				return;
			}
		}
	}
}