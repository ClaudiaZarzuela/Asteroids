#include "../src/checkML.h"
#include "GameState.h"
#include "../src/game/Game.h"

// constructora
GameState::GameState() {
	manager_ = new Manager();
	x = (sdlutils().width() - Game::instance()->getText(PAUSA)->width()) / 2;
	y = ((sdlutils().height() - Game::instance()->getText(PAUSA)->height()) / 2) + 100;
	//input_ = InputHandler::instance();
};

// Llama al update de los objetos de la lista de gameObjects
void GameState::update() {
	manager_->update();
};

void GameState::refresh() {
	manager_->refresh();
}
