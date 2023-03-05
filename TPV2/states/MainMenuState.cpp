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
	Entity* caza = manager_->addEntity();
	caza->addComponent<Transform>(Vector2D(sdlutils().width() / 2 - 25, sdlutils().height() / 2), Vector2D(0, 0), 50, 50, 0);
	caza->addComponent<Health>(Game::instance()->getTexture(HEALTH), 3);
	caza->addComponent<Image>(Game::instance()->getTexture(NAVE));

	x = (sdlutils().width() - Game::instance()->getText(MAINMENU)->width()) / 2;
	y = (sdlutils().height() - Game::instance()->getText(MAINMENU)->height()) / 3;
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
			Game::instance()->gameStateMachine->changeState(new PlayState());
			inputChangeState = false;
		}

	}
}