#include "../src/checkML.h"
#include "GameOverState.h"
#include "../src/sdlutils/InputHandler.h"
#include "PlayState.h"
// Identificador de clase de estado
const string GameOverState::gameOverID = "GAMEOVER";
// Constructora de la clase, que difine sus botones y fondo
GameOverState::GameOverState(string info, PlayState* play) : GameState() {
	inputCheck = manager_->addEntity();
	play_ = play;
	if (info == "Win") {
		inputCheck->addComponent<TextRender>(Game::instance()->getText(PAUSA), Game::instance()->getText(WIN), x, y);
	}
	else {
		inputCheck->addComponent<TextRender>(Game::instance()->getText(PAUSA), Game::instance()->getText(LOSE), x, y);
	}
}

// cambia al MainMenuState si se pulsa el espacio
void GameOverState::inputHandler() {
	GameState::inputHandler();
	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			Game::instance()->gameStateMachine->changeState(new MainMenuState(play_));
			inputChangeState = false;
		}
	}
}
