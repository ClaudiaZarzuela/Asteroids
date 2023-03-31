#include "CollisionsSystem.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../components/Health.h"

void CollisionsSystem::recieve(const ecs::Message& m) {

}
// Inicializar el sistema, etc.
void CollisionsSystem::initSystem() {

}
// Si el juego está parado no hacer nada, en otro caso comprobar colisiones como
// en la práctica 1 y enviar mensajes correspondientes.
void CollisionsSystem::update() {
	if (active_) {
		vector<Entity*> ast = mngr_->getEntities(ecs::_grp_ASTEROIDS);
		vector<Entity*> bull = mngr_->getEntities(ecs::_grp_BULLETS);

		auto playerTransform = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::FIGHTER));
		auto player = mngr_->getHandler(ecs::FIGHTER);

		for (int i = 0; i < ast.size(); ++i) {
			auto asteroide = mngr_->getComponent<Transform>(ast[i]);
			if (Collisions::collidesWithRotation(playerTransform->getPos(), playerTransform->getW(), playerTransform->getH(), playerTransform->getRot(),
				asteroide->getPos(), asteroide->getW(), asteroide->getH(), asteroide->getRot())) {

				ifCollision();

				break;
			}
			for (auto ot = mngr_->getEntities(ecs::_grp_BULLETS).begin(); ot != mngr_->getEntities(ecs::_grp_BULLETS).end(); ++ot) {
				auto bala = mngr_->getComponent<Transform>((*ot));
				if (Collisions::collidesWithRotation(bala->getPos(), bala->getW(), bala->getH(), bala->getRot(),
					asteroide->getPos(), asteroide->getW(), asteroide->getH(), asteroide->getRot())) {
					sdlutils().soundEffects().at("gunshot").play();
					mngr_->setAlive((*ot), false);
					ecs::Message m; m.id = ecs::_m_STAR_SHOT; m.star_eaten_data.e = ast[i];
					mngr_->send(m, true);
					//aMngr_->onCollision((ast[i]));
					break;
				}
			}
		}
	}
}

void CollisionsSystem::ifCollision() {
	auto player = mngr_->getHandler(ecs::FIGHTER);
	sdlutils().soundEffects().at("explosion").play();
	mngr_->getComponent<Health>(player)->loseLife();
	for (auto b : mngr_->getEntities(ecs::_grp_BULLETS)) mngr_->setAlive(b, false);
	mngr_->getComponent<Transform>(player)->reset();

	if (mngr_->getComponent<Health>(player)->getLives() <= 0) {
		//playState_->callGameOver("Lose");
	}
	//else { playState_->changeState(); }

	ecs::Message m; m.id = ecs::_m_ROUND_OVER; 
	//aMngr_->destroyAllAsteroids();
}

// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
void CollisionsSystem::onRoundOver() {

}
// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
void CollisionsSystem::onRoundStart() {

}