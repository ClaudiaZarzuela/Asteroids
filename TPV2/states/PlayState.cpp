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
	caza = manager_->addEntity();
	manager_->setHandler(ecs::FIGHTER, caza);
	caza->addComponent<Transform>(Vector2D(sdlutils().width()/2 - 25, sdlutils().height()/2), Vector2D(0, 0), 50, 50, 0);
	caza->addComponent<ShowAtOppositeSide>();
	caza->addComponent<DeAcceleration>();
	caza->addComponent<Gun>(Game::instance()->getTexture(BULLET));
	caza->addComponent<FighterCtrl>();
	caza->addComponent<Health>(Game::instance()->getTexture(HEALTH), 3);
	caza->addComponent<Image>(Game::instance()->getTexture(NAVE));
	aManager = new AsteroidManager(manager_);
	cManager = new CollisionsManager(aManager, manager_, this);
}

void PlayState::startGame() {
	//manager_->refresh();
	resetAsteroids();
	caza->getComponent<Health>()->resetLives();
}
void PlayState::resetGame() {
	//manager_->refresh();
	aManager->destroyAllAsteroids();
	for (auto b : manager_->getEntities(ecs::_grp_BULLETS)) b->setAlive(false);
	caza->getComponent<Transform>()->reset();
	//manager_->refresh();
}
void PlayState::resetAsteroids() {
	aManager->createAsteroids(10);
}
void PlayState::update() {
    cManager->checkCollision();
	aManager->addAsteroidFrequently();
	GameState::update();
}

void PlayState::inputHandler() {
	GameState::inputHandler();
	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
	if (!inputChangeState && InputHandler::instance()->allKeysUp()) inputChangeState = true;
	if (inputChangeState) {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			cout << "Cambio al estado de pausa" << endl;
			Game::instance()->gameStateMachine->pushState(new PauseState());
			inputChangeState = false;
		}
	}
}

void PlayState::changeRestartState() {
	Game::instance()->gameStateMachine->pushState(new RestartGameState());
	inputChangeState = false;
}
void PlayState::changeGameOvertState(string info) {
	Game::instance()->gameStateMachine->pushState(new GameOverState(info));
	inputChangeState = false;
}