#include "AsteroidManager.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"
#include "../components/Follow.h"
#include "Game.h"

void AsteroidManager::createAsteroids(int numAst, int newGen) {
	for (int i = 0; i < numAst; ++i) {
		Vector2D p = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), sdlutils().rand().nextInt(0, sdlutils().height()));
		Vector2D c = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2) + Vector2D(sdlutils().rand().nextInt(-100, 100), sdlutils().rand().nextInt(-100, 100));
		float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
		Vector2D v = (c - p).normalize() * speed;
		Entity* as = mngr_->addEntity(ecs::_grp_ASTEROIDS);
		as->addComponent<Generations>(newGen);
		as->addComponent<Transform>(p, v, 10.0f + 5.0f* as->getComponent<Generations>()->getGeneration(), 10.0f + 5.0f * as->getComponent<Generations>()->getGeneration(), 0);
		as->addComponent<ShowAtOppositeSide>();
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
	for (auto it = mngr_->getEntitiesByGroup(ecs::_grp_ASTEROIDS).begin(); it != mngr_->getEntitiesByGroup(ecs::_grp_ASTEROIDS).end(); ++it) {
		(*it)->setAlive(false);
	}
}

void AsteroidManager::onCollision(Entity* a) {
	a->setAlive(false);
	currAsteroids--;
	if (a->getComponent<Generations>()->getGeneration() > 1 && currAsteroids < 30) { 
		auto r = sdlutils().rand().nextInt(0, 360);
		auto pos = a->getComponent<Transform>()->getPos() + a->getComponent<Transform>()->getVel().rotate(r) * 2 * max(a->getComponent<Transform>()->getW(), a->getComponent<Transform>()->getH());
		auto vel = a->getComponent<Transform>()->getVel().rotate(r) * 1.1f;
		
		Entity* as1 = mngr_->addEntity(ecs::_grp_ASTEROIDS); Entity* as2 = mngr_->addEntity(ecs::_grp_ASTEROIDS);
		as1->addComponent<Generations>(a->getComponent<Generations>()->getGeneration() - 1);
		as2->addComponent<Generations>(a->getComponent<Generations>()->getGeneration() - 1);

		as1->addComponent<Transform>(pos, vel, 10.0f + 5.0f * as1->getComponent<Generations>()->getGeneration(), 10.0f + 5.0f * as1->getComponent<Generations>()->getGeneration(), 0);
		as2->addComponent<Transform>(pos, vel, 10.0f + 5.0f * as1->getComponent<Generations>()->getGeneration(), 10.0f + 5.0f * as1->getComponent<Generations>()->getGeneration(), 0);

		as1->addComponent<ShowAtOppositeSide>();
		as2->addComponent<ShowAtOppositeSide>();

		if (a->hasComponent<Follow>()) {
			as1->addComponent<Follow>();
			as2->addComponent<Follow>();

			as1->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID_GOLD));
			as2->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID_GOLD));
		}
		else { as1->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID)); as2->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID)); }
	}
}