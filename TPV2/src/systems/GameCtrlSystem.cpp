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
void onCollision_FighterAsteroid() {

}
// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
void onAsteroidsExtinction() {

}

void GameCtrlSystem::update() {
	if (input_->isKeyDown(SDLK_SPACE)) {
		ecs::Message m; m.id = ecs::_m_CHANGE_STATE;
		switch (currentState)
		{
		case System::MAINMENU:
			currentState = System::PLAY;
			break;
		case System::PLAY:
			currentState = System::PAUSE;
			break;
		case System::PAUSE:
			currentState = System::PLAY;
			break;
		case System::GAMEOVER:
			currentState = System::MAINMENU;
			break;
		case System::RESTART:
			currentState = System::PLAY;
			break;
		default:
			break;
		}
		mngr_->send(m, true);
	}
}