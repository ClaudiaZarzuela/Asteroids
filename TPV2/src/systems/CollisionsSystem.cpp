#include "CollisionsSystem.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../components/Health.h"
#include "../checkML.h"

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void CollisionsSystem::recieve(const ecs::Message& m) {
	switch (m.id)
	{
		case ecs::_m_ONLINE:
			host = false; break;

		case ecs::_m_PAUSE:
		case ecs::_m_ROUND_OVER:
			onRoundOver(); break;

		case ecs::_m_ROUND_START:
		case ecs::_m_PLAY:
			onRoundStart(); break;

		case ecs::_m_SINGLEPLAYER:
			online = false;
			onRoundStart(); break;

		case ecs::_m_ONLINE:
			host = false;
			break;

		case ecs::_m_START_ONLINE_ROUND:
			online = true;
			onRoundStart(); break;

		case ecs::_m_HOST:
			host = true;
		default: break;
	}
}

// Si el juego está parado no hacer nada, en otro caso comprobar colisiones como
// en la práctica 1 y enviar mensajes correspondientes.
void CollisionsSystem::update() {
	if (active_) {
		if (!online) {
			vector<Entity*> ast = mngr_->getEntities(ecs::_grp_ASTEROIDS);
			vector<Entity*> bull = mngr_->getEntities(ecs::_grp_BULLETS);

			auto playerTransform = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::FIGHTER));
			auto player = mngr_->getHandler(ecs::FIGHTER);

			for (int i = 0; i < ast.size(); ++i) {
				auto asteroide = mngr_->getComponent<Transform>(ast[i]);
				if (Collisions::collidesWithRotation(playerTransform->getPos(), playerTransform->getW(), playerTransform->getH(), playerTransform->getRot(),
					asteroide->getPos(), asteroide->getW(), asteroide->getH(), asteroide->getRot())) {

					ecs::Message m; m.id = ecs::_m_FIGHTER_CRASHED; m.star_crashed_data.a = ast[i];
					mngr_->send(m, true);
					break;
				}
				for (auto ot = mngr_->getEntities(ecs::_grp_BULLETS).begin(); ot != mngr_->getEntities(ecs::_grp_BULLETS).end(); ++ot) {
					auto bala = mngr_->getComponent<Transform>((*ot));
					if (Collisions::collidesWithRotation(bala->getPos(), bala->getW(), bala->getH(), bala->getRot(),asteroide->getPos(), asteroide->getW(), asteroide->getH(), asteroide->getRot())) {
					
						ecs::Message m; m.id = ecs::_m_STAR_SHOT; m.star_shot_data.asteroid = ast[i];  m.star_shot_data.bullet = (*ot);
						mngr_->send(m, true);
						break;
					}
				}
			}
		}
		else {
			Transform* player;
			Transform* enemy;
			if (host) {
				player = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::PLAYER1));
				enemy = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::PLAYER2));
			}
			else {
				player = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::PLAYER2));
				enemy = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::PLAYER1));
			}

			vector<Entity*> eBullets = mngr_->getEntities(ecs::_grp_ENEMY_BULLETS);
			for (int i = 0; i < eBullets.size(); ++i) {
				auto eBull = mngr_->getComponent<Transform>(eBullets[i]);
				if (Collisions::collidesWithRotation(player->getPos(), player->getW(), player->getH(), player->getRot(),
					eBull->getPos(), eBull->getW(), eBull->getH(), eBull->getRot())) {
					sdlutils().soundEffects().at("explosion").play();
					ecs::Message m; m.id = ecs::_m_PLAYER_SHOT; 
					if (host) m.player_shot_data.playerWinner = 3;
					else  m.player_shot_data.playerWinner = 2;
						mngr_->send(m, true); break;
				}
			}

			vector<Entity*> bullets = mngr_->getEntities(ecs::_grp_BULLETS);
			for (int j = 0; j < bullets.size(); ++j) {
				auto bull = mngr_->getComponent<Transform>(bullets[j]);
				if (Collisions::collidesWithRotation(enemy->getPos(), enemy->getW(), enemy->getH(), enemy->getRot(),
					bull->getPos(), bull->getW(), bull->getH(), bull->getRot())) {
					sdlutils().soundEffects().at("explosion").play();
					ecs::Message m; m.id = ecs::_m_PLAYER_SHOT;
					if (host) m.player_shot_data.playerWinner = 2;
					else  m.player_shot_data.playerWinner = 3;
					mngr_->send(m, true); break;
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