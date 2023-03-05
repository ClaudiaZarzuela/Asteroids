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
	fighter = manager_->addEntity();
	manager_->setHandler(ecs::FIGHTER, fighter);
	fighter->addComponent<Transform>(Vector2D(sdlutils().width()/2 - 25, sdlutils().height()/2), Vector2D(0, 0), 50, 50, 0);
	fighter->addComponent<ShowAtOppositeSide>();
	fighter->addComponent<DeAcceleration>();
	fighter->addComponent<Gun>(Game::instance()->getTexture(BULLET));
	fighter->addComponent<FighterCtrl>();
	fighter->addComponent<Health>(Game::instance()->getTexture(HEALTH), 3);
	fighter->addComponent<Image>(Game::instance()->getTexture(NAVE));

	aManager = new AsteroidManager(manager_);
	cManager = new CollisionsManager(aManager, manager_, this); // hay que llamar a su check collisions pero no se desde donde jeje

}

// actualiza el PlayState
void PlayState::update() {
	if (manager_->getEntities(ecs::_grp_ASTEROIDS).size() == 0) {
		for (auto b : manager_->getEntities(ecs::_grp_BULLETS)) b->setAlive(false);
		fighter->getComponent<Transform>()->reset();
		callGameOver("Win");
	}
    cManager->checkCollision();
	aManager->addAsteroidFrequently();
	GameState::update();
}

// comprueba si se pulsa space para cambiar de estado
void PlayState::inputHandler() {
	GameState::inputHandler();
	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			Game::instance()->gameStateMachine->pushState(new PauseState());
			inputChangeState = false;
		}
	}
}

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
		fighter->getComponent<Health>()->resetLives();
	}
}