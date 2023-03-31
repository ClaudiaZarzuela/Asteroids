#include "GameCtrlSystem.h"

void GameCtrlSystem::recieve(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_STAR_SHOT: score_ += 1; break;
	case ecs::_m_FIGHTER_CRASHED:
		onCollision_FighterAsteroid();
		/*ecs::Message m; m.id = ecs::_m_ROUND_OVER;
		mngr_->send(m, true);*/ break;

	default: break;
	}
}

// Para gestionar el mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
	// al fighter, y si no hay más vidas avisar que ha acabado el juego (y quien
	// es el ganador).
void GameCtrlSystem::onCollision_FighterAsteroid() {

}
// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {

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