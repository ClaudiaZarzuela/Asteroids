#include "../src/checkML.h"
#include "GameOverState.h"
#include "../src/sdlutils/InputHandler.h"

// Identificador de clase de estado
const string GameOverState::gameOverID = "GAMEOVER";
// Constructora de la clase, que difine sus botones y fondo
GameOverState::GameOverState(string info) : GameState() {
	inputCheck = manager_->addEntity();
	if (info == "Win") {
		inputCheck->addComponent<TextRender>(Game::instance()->getText(PAUSA), Game::instance()->getText(WIN), x, y);
	}
	else {
		inputCheck->addComponent<TextRender>(Game::instance()->getText(PAUSA), Game::instance()->getText(LOSE), x, y);
	}
}

void GameOverState::inputHandler() {
	GameState::inputHandler();
	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			cout << "Cambio al mainMenu" << endl;
			auto playSt = dynamic_cast<PlayState*>(Game::instance()->gameStateMachine->lastState());
			playSt->resetGame();
			Game::instance()->gameStateMachine->changeState(new MainMenuState());
			inputChangeState = false;
		}
	}
}
