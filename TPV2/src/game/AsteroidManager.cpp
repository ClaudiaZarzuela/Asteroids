#include "AsteroidManager.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"
#include "../components/Follow.h"
#include "Game.h"

void AsteroidManager::createAsteroids(int numAst, int newGen) {
	for (int i = 0; i < numAst; ++i) {
		Entity* as = mngr_->addEntity(ecs::_grp_ASTEROIDS);
		as->addComponent<Transform>(Vector2D(500, 500), Vector2D(0, 0), 50, 50, 0);
		as->addComponent<ShowAtOppositeSide>();
		as->addComponent<Generations>(newGen);
		if (sdlutils().rand().nextInt(0, 10) < 3) {
			as->addComponent<Follow>();
			as->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID_GOLD));
		}
		else {
			as->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID));
		}
	}
	currAsteroids += numAst;
}

void AsteroidManager::addAsteroidFrequently() {

}

void AsteroidManager::update() {

}
void AsteroidManager::destroyAllAsteroids() {

}

void AsteroidManager::onCollision(Entity* a) {
	a->setAlive(false);
	if (a->getComponent<Generations>()->getGeneration() > 1 && currAsteroids < 30) createAsteroids(2, a->getComponent<Generations>()->getGeneration() - 1);
}