#include "BulletSystem.h"
#include "../components/Transform.h"

void BulletSystem::recieve(const ecs::Message& m) {
	switch (m.id)
	{
	case ecs::_m_SHOOT:
		//shoot(); break;
	case ecs::_m_STAR_SHOT:
		onCollision_BulletAsteroid(m.star_eaten_data.e); break;
	case ecs::_m_ROUND_OVER:
		onRoundOver(); break;
	case ecs::_m_ROUND_START:
		onRoundStart(); break;
	default:
		break;
	}
}
// Inicializar el sistema, etc.
void BulletSystem::initSystem() {

}
// Si el juego está parado no hacer nada, en otro caso mover las balas y
// desactivar las que salen de la ventana como en la práctica 1.
void BulletSystem::update() {
	if (active_) {
		for (auto e : mngr_->getEntities(ecs::_grp_BULLETS)) {
			auto tr = mngr_->getComponent<Transform>(e);
			tr->getPos() = tr->getPos() + tr->getVel();
			tr->setRot(tr->getRot() + 5.0f);
		}
	}
}

// Para gestionar el mensaje de que el jugador ha disparado. Añadir una bala al
// juego, como en la práctica 1. Recuerda que la rotación de la bala sería
// vel.angle(Vector2D(0.0f,-1.0f))
void BulletSystem::shoot(Vector2D pos, Vector2D vel, double width, double height) {

	/*Entity* bullet = mngr_->addEntity(ecs::_grp_BULLETS);
	Vector2D bPos = tr_->getPos()
		+ Vector2D(tr_->getW() / 2.0f, tr_->getH() / 2.0f)
		- Vector2D(0.0f, tr_->getH() / 2.0f + 5.0f + 12.0f).rotate(tr_->getRot())
		- Vector2D(2.0f, 10.0f);
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(tr_->getRot()) * (tr_->getVel().magnitude() + 5.0f);
	bullet->addComponent<Transform>(bPos, bVel, 5, 20, tr_->getRot());
	bullet->addComponent<Image>(tex_);
	bullet->addComponent<DisableOnExit>();*/

}
// Para gestionar el mensaje de que ha habido un choque entre una bala y un
// asteroide. Desactivar la bala “b”.
void BulletSystem::onCollision_BulletAsteroid(Entity* b) {
	mngr_->setAlive(b, false);
}
// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
// balas, y desactivar el sistema.
void BulletSystem::onRoundOver() {
	for (auto e : mngr_->getEntities(ecs::_grp_BULLETS)) {
		mngr_->setAlive(e, false);
	}
	active_ = false;
}
// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
void BulletSystem::onRoundStart() {
	active_ = true;
}