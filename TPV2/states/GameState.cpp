#include "GameState.h"

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


