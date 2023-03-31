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
	// al fighter, y si no hay más vidas avisar que ha acabado el juego
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
// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {
	ecs::Message m1; m1.id = ecs::_m_ROUND_OVER;
	mngr_->send(m1, true);
	ecs::Message m2; m2.id = ecs::_m_GAME_OVER;
	mngr_->send(m2, true);

}

void GameCtrlSystem::update() {
	if (input_->isKeyJustDown(SDLK_SPACE)) {
		ecs::Message m;
		m.id = ecs::_m_ROUND_START;
		switch (currentState)
		{
		case MAINMENU:
			currentState = PLAY;
			m.id = ecs::_m_ROUND_START;
			std::cout << "Cambio a " << currentState << std::endl;
			break;
		case PLAY:
			currentState = PAUSE;
			std::cout << "Cambio a " << currentState << std::endl;
			break;
		case PAUSE:
			currentState = PLAY;
			std::cout << "Cambio a " << currentState << std::endl;
			break;
		case GAMEOVER:
			currentState = MAINMENU;
			std::cout << "Cambio a " << currentState << std::endl;
			break;
		case RESTART:
			currentState = PLAY;
			std::cout << "Cambio a " << currentState << std::endl;
			break;
		default:
			break;
		}
		mngr_->send(m, true);
	}
}