#include "PauseState.h"
#include "../src/sdlutils/InputHandler.h"
// Identificador de clase de estado
const string PauseState::pauseID = "PAUSE";

// Constructora de la clase, que difine sus botones y fondo
PauseState::PauseState() : GameState() {
	x = (sdlutils().width() - Game::instance()->getText(PAUSA)->width()) / 2;
	y = (sdlutils().height() - Game::instance()->getText(PAUSA)->height()) / 2;
	inputCheck = manager_->addEntity();
	inputCheck->addComponent<TextRender>(Game::instance()->getText(PAUSA), x, y);
}


void PauseState::inputHandler() {
	GameState::inputHandler();
	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			cout << "Cambio al playState" << endl;
			Game::instance()->gameStateMachine->currentState()->deleteState();
			Game::instance()->gameStateMachine->popState();
			inputChangeState = false;
		}
	}
}
