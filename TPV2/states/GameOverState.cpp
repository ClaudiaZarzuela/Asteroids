#include "../src/checkML.h"
#include "GameOverState.h"
#include "../src/sdlutils/InputHandler.h"
#include "PlayState.h"
#include "../src/components/TextRender.h"
// Identificador de clase de estado
const string GameOverState::gameOverID = "GAMEOVER";
// Constructora de la clase, que difine sus botones y fondo
GameOverState::GameOverState(string info, PlayState* play) : GameState() {
	Entity* text_ = manager_->addEntity(ecs::_grp_TEXT);
	play_ = play;
	if (info == "Win") {
		manager_->addComponent<TextRender>(text_, Game::instance()->getText(PAUSA), Game::instance()->getText(WIN), x, y);
	}
	else {
		manager_->addComponent<TextRender>(text_, Game::instance()->getText(PAUSA), Game::instance()->getText(LOSE), x, y);
	}
}

//// cambia al MainMenuState si se pulsa el espacio
void GameOverState::update() {
	if (!inputChangeState && input_->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (input_->isKeyDown(SDLK_SPACE)) {
			Game::instance()->gameStateMachine->changeState(new MainMenuState(play_));
			inputChangeState = false;
		}
	}
}