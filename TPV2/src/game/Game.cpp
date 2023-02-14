#include "Game.h"

void Game::init() {
	//�
		manager_ = new Manager();
	//�
		Entity* ball = manager_->addEntity();
	//�
		manager_->setHandler(ecs::BALL, ball);
	//�
}

void Game::run() {
	while (!exit_) {
		//�
		manager_->update();
		//�
		sdlutils().clearRenderer();
		manager_->render();
		sdlutils().presentRenderer();
		//�
		manager_->refresh();
		//�
	}
}