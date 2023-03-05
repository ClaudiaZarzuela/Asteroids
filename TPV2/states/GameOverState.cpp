#include "GameOverState.h"
#include "../src/sdlutils/InputHandler.h"
// Identificador de clase de estado
const string GameOverState::gameOverID = "GAMEOVER";
// Constructora de la clase, que difine sus botones y fondo
GameOverState::GameOverState(string info) : GameState() {
	x = (sdlutils().width() - Game::instance()->getText(PAUSA)->width()) / 2;
	y = (sdlutils().height() - Game::instance()->getText(PAUSA)->height()) / 2;
	inputCheck = manager_->addEntity();
	inputCheck->addComponent<TextRender>(Game::instance()->getText(PAUSA), x, y);
}


void GameOverState::inputHandler() {
	GameState::inputHandler();
	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			cout << "Cambio al mainMenu" << endl;
			Game::instance()->gameStateMachine->currentState()->deleteState();
			Game::instance()->gameStateMachine->changeState(new MainMenuState());
			inputChangeState = false;
		}
	}
}
