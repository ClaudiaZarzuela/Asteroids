#include "../src/checkML.h"
#include "PauseState.h"
#include "../src/sdlutils/InputHandler.h"
#include "../src/components/TextRender.h"
// Identificador de clase de estado
const string PauseState::pauseID = "PAUSE";

// Constructora de la clase, que difine sus botones y fondo
PauseState::PauseState() : GameState() {
	Entity* text_ = manager_->addEntity(ecs::_grp_TEXT);
	manager_->addComponent<TextRender>(text_, Game::instance()->getText(PAUSA), x, y);
}

// cambia al estado de PlayState si se pulsa el space
void PauseState::update() {
	if (!inputChangeState && input_->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (input_->isKeyDown(SDLK_SPACE)) {
			Game::instance()->gameStateMachine->currentState()->deleteState();
			Game::instance()->gameStateMachine->popState();
			inputChangeState = false;
		}
	}
}