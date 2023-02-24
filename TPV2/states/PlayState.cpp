#include "PlayState.h"
#include "../src/components/Image.h"
#include "../src/components/Transform.h"
#include "../src/components/FighterCtrl.h"
#include "../src/components/ShowAtOppositeSide.h"
#include "../src/components/DeAcceleration.h"
#include "../src/components/FramedImage.h"
#include "../src/components/Health.h"
#include "../src/components/Gun.h"

// Identificador de clase de estado
const string PlayState::playID = "PLAY";

// Constructora de la clase, que inizializa todos los elementos del juego
PlayState::PlayState(Game* game) :GameState(game) {//Creamos las paredes
	caza = manager_->addEntity();
	caza->addComponent<Transform>(Vector2D(500,500), Vector2D(0, 0), 50, 50, 0);
	caza->addComponent<ShowAtOppositeSide>();
	caza->addComponent<DeAcceleration>();
	caza->addComponent<FighterCtrl>();
	caza->addComponent<Gun>();
	caza->addComponent<Health>(game->getTexture(HEALTH), 3);
	caza->addComponent<Image>(game->getTexture(NAVE));

	asteroids = manager_->addEntity(ecs::_grp_ASTEROIDS);
	asteroids->addComponent<Transform>(Vector2D(500, 500), Vector2D(0, 0), 50, 50, 0);
	asteroids->addComponent<FramedImage>(game->getTexture(ASTEROID));
	
}
