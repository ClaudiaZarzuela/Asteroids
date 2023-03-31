#include "../src/checkML.h"
#include "RestartGameState.h"
#include "../src/sdlutils/InputHandler.h"
#include "PlayState.h"
#include "../src/components/TextRender.h"
// Identificador de clase de estado
const string RestartGameState::restartID = "RESTART";
// Constructora de la clase, que difine sus botones y fondo
RestartGameState::RestartGameState(PlayState* play) : GameState() {
	play_ = play;
	Entity* text_ = manager_->addEntity(ecs::_grp_TEXT);
	manager_->addComponent<TextRender>(text_, Game::instance()->getText(PAUSA), x, y);
}

// cambia al estado de PlayState cuando se pulsa el space
void RestartGameState::update() {
	if (!inputChangeState && input_->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (input_->isKeyDown(SDLK_SPACE)) {
			play_->startGame();
			Game::instance()->gameStateMachine->currentState()->deleteState();
			Game::instance()->gameStateMachine->popState();
			inputChangeState = false;
		}
	}
}
