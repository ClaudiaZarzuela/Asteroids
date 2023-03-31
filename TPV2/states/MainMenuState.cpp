#include "../src/checkML.h"
#include "MainMenuState.h"
#include "../src/game/Game.h"
#include "../src/components/Image.h"
#include "../src/components/Transform.h"
#include "../src/components/Health.h"
#include "PlayState.h"
#include "../src/components/TextRender.h"
// Identificador de clase de estado
const string MainMenuState::menuID = "MENU";

// Constructora de la clase, que difine sus botones y fondo
MainMenuState::MainMenuState(PlayState* playSt) :GameState() {
	playSt_ = playSt;
	Entity* text_ = manager_->addEntity(ecs::_grp_TEXT);
	manager_->addComponent<TextRender>(text_, Game::instance()->getText(MAINMENU), x, y);
}

// cambia al estado de PlayState si se pulsa el space
void MainMenuState::update() {
	if (!inputChangeState && input_->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (input_->isKeyDown(SDLK_SPACE)) {
			playSt_->startGame(true);
			Game::instance()->gameStateMachine->currentState()->deleteState();
			Game::instance()->gameStateMachine->popState();
			inputChangeState = false;
		}

	}
}