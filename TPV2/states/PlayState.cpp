#include "PlayState.h"
#include "../src/components/Image.h"
#include "../src/components/Transform.h"

// Identificador de clase de estado
const string PlayState::playID = "PLAY";

// Constructora de la clase, que inizializa todos los elementos del juego
PlayState::PlayState(Game* game) :GameState(game) {//Creamos las paredes
	caza = manager_->addEntity();
	caza->addComponent<Transform>(Vector2D(100,100), Vector2D(0, 0), 10, 10, 0);
	caza->addComponent<Image>(game->getTexture(NAVE));
	asteroids = manager_->addEntity();
}
