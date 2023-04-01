#include "BulletSystem.h"
#include "../components/Transform.h"

void BulletSystem::recieve(const ecs::Message& m) {
	switch (m.id)
	{
		case ecs::_m_SHOOT:
			shoot(m.bullet_data.pos, m.bullet_data.vel, m.bullet_data.width, m.bullet_data.height, m.bullet_data.rot); break;
		
		case ecs::_m_STAR_SHOT:
			onCollision_BulletAsteroid(m.star_shot_data.bullet); break;

		case ecs::_m_PAUSE:
			onRoundOver(); break;

		case ecs::_m_ROUND_OVER:
			onRoundOver(); 
			for (auto e : mngr_->getEntities(ecs::_grp_BULLETS)) {
				mngr_->setAlive(e, false);
			}
			break;

		case ecs::_m_PLAY:
		case ecs::_m_ROUND_START:
			onRoundStart(); break;

		default: break;
	
	}
}
// Inicializar el sistema, etc.
void BulletSystem::initSystem() {

}
// Si el juego est� parado no hacer nada, en otro caso mover las balas y
// desactivar las que salen de la ventana como en la pr�ctica 1.
void BulletSystem::update() {
	if (active_) {
		for (auto e : mngr_->getEntities(ecs::_grp_BULLETS)) {
			auto tr = mngr_->getComponent<Transform>(e);
			tr->setPos(tr->getPos() + tr->getVel());
			//tr->setRot(tr->getRot() + 5.0f);
			if (tr->getPos().getX() > sdlutils().width() || tr->getPos().getX() < 0 - tr->getW() ||
				tr->getPos().getY() > sdlutils().height() || tr->getPos().getY() < 0 - tr->getH()) {
				mngr_->setAlive(e, false);
			}
		}
	}
}

// Para gestionar el mensaje de que el jugador ha disparado. A�adir una bala al
// juego, como en la pr�ctica 1. Recuerda que la rotaci�n de la bala ser�a
// vel.angle(Vector2D(0.0f,-1.0f))
void BulletSystem::shoot(Vector2D pos, Vector2D vel, double width, double height, double rot) {
	sdlutils().soundEffects().at("fire").play();
	Entity* bullet = mngr_->addEntity(ecs::_grp_BULLETS);
	mngr_->addComponent<Transform>(bullet, pos, vel, width, height, rot);
	//mngr_->addComponent<Image>(bullet, tex_);
}
// Para gestionar el mensaje de que ha habido un choque entre una bala y un
// asteroide. Desactivar la bala �b�.
void BulletSystem::onCollision_BulletAsteroid(Entity* b) {
	mngr_->setAlive(b, false);
}
// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
// balas, y desactivar el sistema.
void BulletSystem::onRoundOver() {
	active_ = false;
}
// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
void BulletSystem::onRoundStart() {
	active_ = true;
}