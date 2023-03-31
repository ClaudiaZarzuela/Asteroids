#include "CollisionsSystem.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../components/Health.h"

void CollisionsSystem::recieve(const ecs::Message& m) {
	switch (m.id)
	{
	case ecs::_m_ROUND_OVER:
		onRoundOver(); break;
	case ecs::_m_ROUND_START:
		onRoundStart(); break;
		default:
			break;
	}
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

				ecs::Message m; m.id = ecs::_m_FIGHTER_CRASHED;
				mngr_->send(m, true);
				break;
			}
			for (auto ot = mngr_->getEntities(ecs::_grp_BULLETS).begin(); ot != mngr_->getEntities(ecs::_grp_BULLETS).end(); ++ot) {
				auto bala = mngr_->getComponent<Transform>((*ot));
				if (Collisions::collidesWithRotation(bala->getPos(), bala->getW(), bala->getH(), bala->getRot(),asteroide->getPos(), asteroide->getW(), asteroide->getH(), asteroide->getRot())) {
					
					ecs::Message m; m.id = ecs::_m_STAR_SHOT; m.star_eaten_data.e = ast[i];
					mngr_->send(m, true);
					break;
				}
			}
		}
	}
}

// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
void CollisionsSystem::onRoundOver() {
	active_ = false;
}
// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
void CollisionsSystem::onRoundStart() {
	active_ = true;
}