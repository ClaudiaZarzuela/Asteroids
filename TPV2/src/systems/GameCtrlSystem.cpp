#include "GameCtrlSystem.h"
#include "../components/Health.h"
#include "../components/Transform.h"

void GameCtrlSystem::recieve(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_STAR_SHOT: score_ += 1; break;
	case ecs::_m_FIGHTER_CRASHED:
		onCollision_FighterAsteroid(); break;
	case ecs::_m_STAR_EXTINCTION:
		onAsteroidsExtinction(); break;
	default: break;
	}
}

// Para gestionar el mensaje de que ha habido un choque entre el fighter y un>
	// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
	// al fighter, y si no hay m�s vidas avisar que ha acabado el juego
void GameCtrlSystem::onCollision_FighterAsteroid() {
	auto player = mngr_->getHandler(ecs::FIGHTER);
	sdlutils().soundEffects().at("explosion").play();
	mngr_->getComponent<Health>(player)->loseLife();
	for (auto b : mngr_->getEntities(ecs::_grp_BULLETS)) mngr_->setAlive(b, false);
	mngr_->getComponent<Transform>(player)->reset();

	if (mngr_->getComponent<Health>(player)->getLives() <= 0) {
		ecs::Message m; m.id = ecs::_m_GAME_OVER;
		mngr_->send(m, true);
	}
	else {
		ecs::Message m; m.id = ecs::_m_ROUND_OVER;
		mngr_->send(m, true);
	}
}
// Para gestionar el mensaje de que no hay m�s asteroides. Tiene que avisar que
// ha acabado la ronda y adem�s que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {
	ecs::Message m1; m1.id = ecs::_m_ROUND_OVER;
	mngr_->send(m1, true);
	ecs::Message m2; m2.id = ecs::_m_GAME_OVER;
	mngr_->send(m2, true);

}

void GameCtrlSystem::update() {
	if (input_->isKeyDown(SDLK_SPACE)) {
		ecs::Message m; m.id = ecs::_m_CHANGE_STATE;
		switch (currentState)
		{
		case MAINMENU:
			currentState = PLAY;
			break;
		case PLAY:
			currentState = PAUSE;
			break;
		case PAUSE:
			currentState = PLAY;
			break;
		case GAMEOVER:
			currentState = MAINMENU;
			break;
		case RESTART:
			currentState = PLAY;
			break;
		default:
			break;
		}
		mngr_->send(m, true);
	}
}