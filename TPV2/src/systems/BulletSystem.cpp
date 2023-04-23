#include "BulletSystem.h"
#include "../components/Transform.h"
#include "../checkML.h"

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void BulletSystem::recieve(const ecs::Message& m) {
	switch (m.id)
	{
		//se manda cuando el jugador dispara
		case ecs::_m_SHOOT:
			shoot(m.bullet_data.pos, m.bullet_data.vel, m.bullet_data.width, m.bullet_data.height, m.bullet_data.rot); break;

		//se manda para saber que tu enemigo ha disparado en el modo multiplayer
		case ecs::_m_ENEMY_BULLET:
			shootEnemy(m.bullet_data.pos, m.bullet_data.vel, m.bullet_data.width, m.bullet_data.height, m.bullet_data.rot); break;
		
		//cuando la bala colisiona con un asteroide
		case ecs::_m_STAR_SHOT:
			onCollision_Bullet(m.star_shot_data.bullet); break;

		//para pausar las balas si estas en modo pausa en el singleplayer
		case ecs::_m_PAUSE:
			onRoundOver(); break;

		//se desactiva el sistema y se borran todas las balas creadas al acabar la partida
		case ecs::_m_ROUND_OVER:
			onRoundOver(); 
			for (auto e : mngr_->getEntities(ecs::_grp_BULLETS)) {
				mngr_->setAlive(e, false);
			}
			break;

		//activa el sistema y avisa de que se encuentra en modo multiplayer
		case ecs::_m_START_ONLINE_ROUND:
			onRoundStart(); online = true; break;

		//activa el sistema y avisa de que esta en modo singleplayer
		case ecs::_m_ROUND_START:
		case ecs::_m_PLAY:
		case ecs::_m_SINGLEPLAYER:
			online = false;
			onRoundStart(); break;

		default: break;
	
	}
}

// Si el juego está parado no hacer nada, en otro caso mover las balas y
// desactivar las que salen de la ventana como en la práctica 1.
void BulletSystem::update() {
	if (active_) {
		for (auto e : mngr_->getEntities(ecs::_grp_BULLETS)) {
			auto tr = mngr_->getComponent<Transform>(e);
			tr->setPos(tr->getPos() + tr->getVel());
			if (tr->getPos().getX() > sdlutils().width() || tr->getPos().getX() < 0 - tr->getW() ||
				tr->getPos().getY() > sdlutils().height() || tr->getPos().getY() < 0 - tr->getH()) {
				mngr_->setAlive(e, false);
			}
		}
		if (online) {
			for (auto e : mngr_->getEntities(ecs::_grp_ENEMY_BULLETS)) {
				auto tr = mngr_->getComponent<Transform>(e);
				tr->setPos(tr->getPos() + tr->getVel());
				if (tr->getPos().getX() > sdlutils().width() || tr->getPos().getX() < 0 - tr->getW() ||
					tr->getPos().getY() > sdlutils().height() || tr->getPos().getY() < 0 - tr->getH()) {
					mngr_->setAlive(e, false);
				}
			}
		}
	}
}

// Para gestionar el mensaje de que el jugador ha disparado. Añadir una bala al
// juego, como en la práctica 1. 
void BulletSystem::shoot(Vector2D pos, Vector2D vel, double width, double height, double rot) {
	sdlutils().soundEffects().at("fire").play();
	Entity* bullet = mngr_->addEntity(ecs::_grp_BULLETS);
	mngr_->addComponent<Transform>(bullet, pos, vel, width, height, rot);
}

//Gestiona el mensaje de que el enemigo ha disparado si estas en modo multijugador e instancia la bala donde 
//y como se le indique
void BulletSystem::shootEnemy(Vector2D pos, Vector2D vel, double width, double height, double rot) {
	sdlutils().soundEffects().at("fire").play();
	Entity* bullet = mngr_->addEntity(ecs::_grp_ENEMY_BULLETS);
	mngr_->addComponent<Transform>(bullet, pos, vel, width, height, rot);
}

// Para gestionar el mensaje de que ha habido un choque entre una bala y un
// asteroide. Desactivar la bala “b”.
void BulletSystem::onCollision_Bullet(Entity* b) {
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