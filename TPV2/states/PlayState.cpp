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

	aManager = new AsteroidManager();
	aManager->createAsteroids(10);

	cManager = new CollisionsManager(aManager); // hay que llamar a su check collisions pero no se desde donde jeje
}

void PlayState::update() {
    checkCollision();
	aManager->addAsteroidFrequently();
	GameState::update();
}

void PlayState::checkCollision() {
	vector<Entity*> ast = manager_->getEntities(ecs::_grp_ASTEROIDS);
	vector<Entity*> bull = manager_->getEntities(ecs::_grp_BULLETS);
	Entity* player = manager_->getHandler(ecs::FIGHTER);
	//auto nave = mngr_->getHandler(ecs::FIGHTER)->getComponent<Transform>();

	//for (auto it = mngr_->getEntitiesByGroup(ecs::_grp_ASTEROIDS).begin(); it != mngr_->getEntitiesByGroup(ecs::_grp_ASTEROIDS).end(); ++it) {
	for (int i = 0; i < ast.size(); ++i) {
		if (Collisions::collidesWithRotation(player->getComponent<Transform>()->getPos(), player->getComponent<Transform>()->getW(), player->getComponent<Transform>()->getH(), player->getComponent<Transform>()->getRot(),
			ast[i]->getComponent<Transform>()->getPos(), ast[i]->getComponent<Transform>()->getW(), ast[i]->getComponent<Transform>()->getH(), ast[i]->getComponent<Transform>()->getRot())) {
			//aMngr_->destroyAllAsteroids();
			aManager->onCollision((ast[i]));
		}
		/*auto asteroide = (*it)->getComponent<Transform>();
		for (auto ot = mngr_->getEntitiesByGroup(ecs::_grp_BULLETS).begin(); ot != mngr_->getEntitiesByGroup(ecs::_grp_BULLETS).end(); ++ot) {
			auto bala = (*ot)->getComponent<Transform>();
			if (Collisions::collidesWithRotation(bala->getPos(), bala->getW(), bala->getH(), bala->getRot(), asteroide->getPos(), asteroide->getW(), asteroide->getH(), asteroide->getRot())) {
				(*ot)->setAlive(false);
				aMngr_->onCollision((*it));
				return;
			}
		}	*/

	}

}