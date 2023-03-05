#include "../src/checkML.h"
#include "MainMenuState.h"
#include "../src/game/Game.h"
#include "../src/components/Image.h"
#include "../src/components/Transform.h"
#include "../src/components/Health.h"

// Identificador de clase de estado
const string MainMenuState::menuID = "MENU";

// Constructora de la clase, que difine sus botones y fondo
MainMenuState::MainMenuState() :GameState() {
	x = (sdlutils().width() - Game::instance()->getText(MAINMENU)->width()) / 2;
	inputCheck = manager_->addEntity();
	inputCheck->addComponent<TextRender>(Game::instance()->getText(MAINMENU), x, y);
}
void MainMenuState::inputHandler() {
	GameState::inputHandler();
	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			cout << "Cambio al playState" << endl;
			Game::instance()->gameStateMachine->currentState()->deleteState();
			Game::instance()->gameStateMachine->popState();
			auto playSt = dynamic_cast<PlayState*>(Game::instance()->gameStateMachine->lastState());
			playSt->startGame();
			inputChangeState = false;
		}

	}
}