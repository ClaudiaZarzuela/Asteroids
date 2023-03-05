#include "../src/checkML.h"
#include "RestartGameState.h"
#include "../src/sdlutils/InputHandler.h"

// Identificador de clase de estado
const string RestartGameState::restartID = "RESTART";
// Constructora de la clase, que difine sus botones y fondo
RestartGameState::RestartGameState() : GameState() {
	x = (sdlutils().width() - Game::instance()->getText(PAUSA)->width()) / 2;
	y = (sdlutils().height() - Game::instance()->getText(PAUSA)->height()) / 2;
	inputCheck = manager_->addEntity();
	inputCheck->addComponent<TextRender>(Game::instance()->getText(PAUSA), x, y);
}


void RestartGameState::inputHandler() {
	GameState::inputHandler();
	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			cout << "Cambio al playState" << endl;
			if (Game::instance()->gameStateMachine->lastState()->getStateID() == "PLAY") {
				auto playSt = dynamic_cast<PlayState*>(Game::instance()->gameStateMachine->lastState());
				playSt->getAManager()->destroyAllAsteroids();
				playSt->refresh();
				playSt->getAManager()->createAsteroids(10);
			}
			Game::instance()->gameStateMachine->currentState()->deleteState();
			Game::instance()->gameStateMachine->popState();
			inputChangeState = false;
		}
	}
}
