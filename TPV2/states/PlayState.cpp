#include "PlayState.h"
#include "../src/components/Image.h"
#include "../src/components/Transform.h"
#include "../src/components/FighterCtrl.h"
#include "../src/components/ShowAtOppositeSide.h"
#include "../src/components/DeAcceleration.h"
#include "../src/components/FramedImage.h"
#include "../src/components/Health.h"
#include "../src/components/Gun.h"
#include "../src/game/Game.h"
// Identificador de clase de estado
const string PlayState::playID = "PLAY";

// Constructora de la clase, que inizializa todos los elementos del juego
PlayState::PlayState() :GameState(){//Creamos las paredes

	caza = manager_->addEntity();
	manager_->setHandler(ecs::FIGHTER, caza);
	caza->addComponent<Transform>(Vector2D(500,500), Vector2D(0, 0), 50, 50, 0);
	caza->addComponent<ShowAtOppositeSide>();
	caza->addComponent<DeAcceleration>();
	caza->addComponent<FighterCtrl>();
	caza->addComponent<Gun>(Game::instance()->getTexture(BULLET));
	caza->addComponent<Health>(Game::instance()->getTexture(HEALTH), 3);
	caza->addComponent<Image>(Game::instance()->getTexture(NAVE));


	Entity* as = manager_->addEntity(ecs::_grp_ASTEROIDS);
	as->addComponent<Transform>(Vector2D(500, 500), Vector2D(0, 0), 50, 50, 0);
	as->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID));
}
