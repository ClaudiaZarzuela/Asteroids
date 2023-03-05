#include "RestartGameState.h"
#include "../src/sdlutils/InputHandler.h"
// Identificador de clase de estado
const string RestartGameState::restartID = "RESTART";
// Constructora de la clase, que difine sus botones y fondo
RestartGameState::RestartGameState() : GameState() {
	inputCheck = manager_->addEntity();
	inputCheck->addComponent<TextRender>(Game::instance()->getText(PAUSA), x, y);
}


void RestartGameState::inputHandler() {
	GameState::inputHandler();
	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			cout << "Cambio al playState" << endl;
			auto playSt = dynamic_cast<PlayState*>(Game::instance()->gameStateMachine->lastState());
			playSt->resetAsteroids();
			Game::instance()->gameStateMachine->currentState()->deleteState();
			Game::instance()->gameStateMachine->popState();
			inputChangeState = false;
		}
	}
}
