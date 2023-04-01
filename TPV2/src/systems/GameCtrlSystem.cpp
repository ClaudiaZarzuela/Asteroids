#include "GameCtrlSystem.h"
#include "../components/Health.h"
#include "../components/Transform.h"
#include "../checkML.h"

void GameCtrlSystem::recieve(const ecs::Message& m) {
	switch (m.id) {
		case ecs::_m_STAR_SHOT: 
			score_ += 1; 
			break;

		case ecs::_m_FIGHTER_CRASHED:
			onCollision_FighterAsteroid(); 
			break;

		case ecs::_m_STAR_EXTINCTION:
			onAsteroidsExtinction(); 
			break;

		case ecs::_m_PLAY:
			state_ = PLAY;
			break;

		case ecs::_m_MAINMENU: //pasa al endState
			state_ = MENU;
			break;

		case ecs::_m_RESTART: //pasa al endState
			state_ = RESTART;
			break;

		case ecs::_m_PAUSE: //pasa al pauseState
			state_ = PAUSE;
			break;

		case ecs::_m_GAME_OVER_LOSE: //pasa al playState
			state_ = GAMEOVERLOSE;
			break;

		case ecs::_m_GAME_OVER_WIN: //pasa al playState
			state_ = GAMEOVERWIN;
			break;
		default: break;
	}
}

// Para gestionar el mensaje de que ha habido un choque entre el fighter y un>
	// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
	// al fighter, y si no hay más vidas avisar que ha acabado el juego
void GameCtrlSystem::onCollision_FighterAsteroid() {
	auto player = mngr_->getHandler(ecs::FIGHTER);
	sdlutils().soundEffects().at("explosion").play();
	mngr_->getComponent<Health>(player)->loseLife();
	ecs::Message m1; m1.id = ecs::_m_ROUND_OVER;
	mngr_->send(m1, true);

	if (mngr_->getComponent<Health>(player)->getLives() <= 0) {
		ecs::Message m; m.id = ecs::_m_GAME_OVER_LOSE;
		mngr_->send(m, true);
	}
	else {
		ecs::Message m2; m2.id = ecs::_m_RESTART;
		mngr_->send(m2, true);
	}
}
// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {
	ecs::Message m1; m1.id = ecs::_m_ROUND_OVER;
	mngr_->send(m1, true);
	ecs::Message m2; m2.id = ecs::_m_GAME_OVER_WIN;
	mngr_->send(m2, true);

}

void GameCtrlSystem::update() {
	if (input_->isKeyJustDown(SDLK_SPACE)) {
		ecs::Message m1; ecs::Message m2;
		switch (state_)
			{
			case MAINMENU:
				m1.id = ecs::_m_PLAY;
				m2.id = ecs::_m_ROUND_START;
				break;
			case PLAY:
				m1.id = ecs::_m_PAUSE;
				break;
			case PAUSE:
				m1.id = ecs::_m_PLAY;
				break;
			case GAMEOVERLOSE:
				m1.id = ecs::_m_MAINMENU;
				break;
			case GAMEOVERWIN:
				m1.id = ecs::_m_MAINMENU;
				break;
			case RESTART:
				m1.id = ecs::_m_PLAY;
				m2.id = ecs::_m_ROUND_START;
				break;

			default:
				break;
		}
		mngr_->send(m1, true);
		mngr_->send(m2, true);
	}
}