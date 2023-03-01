#include "GameState.h"

// Llama al update de los objetos de la lista de gameObjects
void GameState::update() {
	manager_->update();
};

// Llama al render de los objetos de la lista de gameObjects
void GameState::render() const {
	manager_->render();
};

// Llama al handleEvents de los objetos de la lista de gameObjects
void GameState::handleEvent(SDL_Event event) {

};

