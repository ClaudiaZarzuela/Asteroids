#include "GameState.h"
#include "../src/game/Game.h"
GameState::GameState() {
	manager_ = new Manager();
	x = (sdlutils().width() - Game::instance()->getText(PAUSA)->width()) / 2;
	y = ((sdlutils().height() - Game::instance()->getText(PAUSA)->height()) / 2) + 100;
};
// Llama al update de los objetos de la lista de gameObjects
void GameState::update() {
	manager_->update();
};

void GameState::refresh() {
	manager_->refresh();
}

// Llama al render de los objetos de la lista de gameObjects
void GameState::render() const {
	manager_->render();
};

void GameState::inputHandler() {
	manager_->inputHandler();
}

