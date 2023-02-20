#include "GameState.h"
#include "../TPV2/src/game/Game.h"

// Llama al update de los objetos de la lista de gameObjects
void GameState::update() {
	for (auto it = gameObjects.begin(); it != gameObjects.end() && !deleted;) {
		(*it)->update();
		if (!deleted) ++it;
		else return;
	}
};

// Llama al render de los objetos de la lista de gameObjects
void GameState::render() const {
	for (auto it = gameObjects.begin(); it != gameObjects.end() && !deleted;) {
		(*it)->render();
		if (!deleted) ++it;
		else return;
	}
};

// Llama al handleEvents de los objetos de la lista de gameObjects
//void GameState::handleEvent(SDL_Event event) {
//	for (auto it = gameObjects.begin(); it != gameObjects.end() && !deleted;) {
//		(*it)->handleEvent(event);
//		if (!deleted) ++it;
//		else return;
//	}
//};

// Destructora de la clase, cuyo comportamiento heredan el resto de estados
GameState:: ~GameState() {
	for (auto it = gameObjects.begin(); it != gameObjects.end();) {
		delete* it;
		(*it) = nullptr;
		it = gameObjects.erase(it);
	}
}
