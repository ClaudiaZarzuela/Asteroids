#include "../src/checkML.h"
#include "MainMenuState.h"
#include "../src/game/Game.h"
#include "../src/components/Image.h"
#include "../src/components/Transform.h"
#include "../src/components/Health.h"
#include "PlayState.h"
// Identificador de clase de estado
const string MainMenuState::menuID = "MENU";

// Constructora de la clase, que difine sus botones y fondo
MainMenuState::MainMenuState(PlayState* playSt) :GameState() {
	playSt_ = playSt;
	inputCheck = manager_->addEntity();
	inputCheck->addComponent<TextRender>(Game::instance()->getText(MAINMENU), x, y);
}

// cambia al estado de PlayState si se pulsa el space
void MainMenuState::inputHandler() {
	GameState::inputHandler();
	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			playSt_->startGame(true);
			Game::instance()->gameStateMachine->currentState()->deleteState();
			Game::instance()->gameStateMachine->popState();
			inputChangeState = false;
		}

	}
}