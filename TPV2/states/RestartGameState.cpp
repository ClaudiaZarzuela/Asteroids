#include "../src/checkML.h"
#include "RestartGameState.h"
#include "../src/sdlutils/InputHandler.h"
#include "PlayState.h"
// Identificador de clase de estado
const string RestartGameState::restartID = "RESTART";
// Constructora de la clase, que difine sus botones y fondo
RestartGameState::RestartGameState(PlayState* play) : GameState() {
	play_ = play;
	inputCheck = manager_->addEntity();
	inputCheck->addComponent<TextRender>(Game::instance()->getText(PAUSA), x, y);
}

// cambia al estado de PlayState cuando se pulsa el space
void RestartGameState::inputHandler() {
	GameState::inputHandler();
	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			play_->startGame();
			Game::instance()->gameStateMachine->currentState()->deleteState();
			Game::instance()->gameStateMachine->popState();
			inputChangeState = false;
		}
	}
}
