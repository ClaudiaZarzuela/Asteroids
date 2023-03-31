#include "../src/checkML.h"
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
#include "../src/sdlutils/SDLUtils.h"

// Identificador de clase de estado
const string PlayState::playID = "PLAY";

// Constructora de la clase, que inizializa todos los elementos del juego
PlayState::PlayState() :GameState(){
	fighter = manager_->addEntity(ecs::_grp_GENERAL);
	manager_->setHandler(ecs::FIGHTER, fighter);
	manager_->addComponent<Transform>(fighter, Vector2D(sdlutils().width()/2 - 25, sdlutils().height()/2), Vector2D(0, 0), 50, 50, 0);
	manager_->addComponent<ShowAtOppositeSide>(fighter);
	manager_->addComponent<DeAcceleration>(fighter);
	manager_->addComponent<Gun>(fighter, Game::instance()->getTexture(BULLET));
	manager_->addComponent<FighterCtrl>(fighter);
	manager_->addComponent<Health>(fighter, Game::instance()->getTexture(HEALTH), 3);
	manager_->addComponent<Image>(fighter, Game::instance()->getTexture(NAVE));

	aManager = new AsteroidManager(manager_);
	cManager = new CollisionsManager(aManager, manager_, this); // hay que llamar a su check collisions pero no se desde donde jeje

}

// actualiza el PlayState
void PlayState::update() {
	if (manager_->getEntities(ecs::_grp_ASTEROIDS).size() == 0) {
		for (auto b : manager_->getEntities(ecs::_grp_BULLETS)) manager_->setAlive(b, false);
		manager_->getComponent<Transform>(fighter)->reset();
		callGameOver("Win");
	}
    cManager->checkCollision();
	aManager->addAsteroidFrequently();
	//GameState::update();
	if (!inputChangeState && input_->allKeysUp()) inputChangeState = true;
	if (!inputChangeState && input_->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (input_->isKeyDown(SDLK_SPACE)) {
			Game::instance()->gameStateMachine->pushState(new PauseState());
			inputChangeState = false;
		}
	}
}
//
//// comprueba si se pulsa space para cambiar de estado
//void PlayState::inputHandler() {
//	GameState::inputHandler();
//	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
//	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
//	if (inputChangeState) {
//		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
//			Game::instance()->gameStateMachine->pushState(new PauseState());
//			inputChangeState = false;
//		}
//	}
//}

// cambia de estado al RestartGameState
void PlayState::changeState() {
	Game::instance()->gameStateMachine->pushState(new RestartGameState(this));
	inputChangeState = false;
}

// cambia de estado al GameOver
void PlayState::callGameOver(string infoState) {
	Game::instance()->gameStateMachine->pushState(new GameOverState(infoState,this));
	inputChangeState = false;
}

// añade los asteroides y las vidas al PlayState
void PlayState::startGame(bool lifes) {
	aManager->createAsteroids(10);
	if (lifes) {
		manager_->getComponent<Health>(fighter)->resetLives();
	}
}