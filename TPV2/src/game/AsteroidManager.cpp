#include "AsteroidManager.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"
#include "../components/Follow.h"
#include "Game.h"
void AsteroidManager::createAsteroids(int n) {
	for (int i = 0; i < n; ++i) {
		Entity* as = mngr_->addEntity(ecs::_grp_ASTEROIDS);
		as->addComponent<Transform>(Vector2D(500, 500), Vector2D(0, 0), 50, 50, 0);
		as->addComponent<ShowAtOppositeSide>();
		as->addComponent<Generations>();
		if (sdlutils().rand().nextInt(0, 10) < 3) {
			as->addComponent<Follow>();
			as->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID_GOLD));
		}
		else {
			as->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID));
		}
	}
	currAsteroids = n;
}

void AsteroidManager::addAsteroidFrequently() {

}

void AsteroidManager::update() {

}
void AsteroidManager::destroyAllAsteroids() {

}