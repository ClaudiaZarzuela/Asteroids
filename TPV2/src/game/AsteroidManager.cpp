#include "AsteroidManager.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"
#include "../components/Follow.h"
#include "Game.h"

void AsteroidManager::createAsteroids(int numAst) {
	for (int i = 0; i < numAst; ++i) {
		int random = sdlutils().rand().nextInt(0, 4);
		Vector2D p;
		switch (random) {
			case 0: p = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), 0); break;
			case 1: p = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), sdlutils().height()); break;
			case 2: p = Vector2D(0, sdlutils().rand().nextInt(0, sdlutils().height())); break;
			case 3: p = Vector2D(sdlutils().width(), sdlutils().rand().nextInt(0, sdlutils().height())); break;
		}
		Vector2D c = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2) + Vector2D(sdlutils().rand().nextInt(-100, 100), sdlutils().rand().nextInt(-100, 100));
		float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
		Vector2D v = (c - p).normalize() * speed;
		Entity* as = mngr_->addEntity(ecs::_grp_ASTEROIDS);
		as->addComponent<Generations>(sdlutils().rand().nextInt(0, 3));
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
	if (sdlutils().currRealTime() - elapsedTime > 5000) {
		createAsteroids(1);
		elapsedTime = sdlutils().currRealTime();
	}
}

void AsteroidManager::destroyAllAsteroids() {
	for (auto it = mngr_->getEntities(ecs::_grp_ASTEROIDS).begin(); it != mngr_->getEntities(ecs::_grp_ASTEROIDS).end(); ++it) {
		(*it)->setAlive(false);
	}
}

void AsteroidManager::onCollision(Entity* a) {
	currAsteroids--;
	a->setAlive(false);
	if (a->getComponent<Generations>()->getGeneration() > 1 && currAsteroids < 30) { 
		auto r = sdlutils().rand().nextInt(0, 360);
		auto pos = a->getComponent<Transform>()->getPos() + a->getComponent<Transform>()->getVel().rotate(r) * 2 * max(a->getComponent<Transform>()->getW(), a->getComponent<Transform>()->getH());
		auto pos2 = Vector2D(pos.getX() + 15, pos.getY() + 15);
		auto vel = a->getComponent<Transform>()->getVel().rotate(r) * 1.1f;
		
		Entity* as1 = mngr_->addEntity(ecs::_grp_ASTEROIDS); Entity* as2 = mngr_->addEntity(ecs::_grp_ASTEROIDS);
		as1->addComponent<Generations>(a->getComponent<Generations>()->getGeneration() - 1);
		as2->addComponent<Generations>(a->getComponent<Generations>()->getGeneration() - 1);

		as1->addComponent<Transform>(pos, vel, 10.0f + 5.0f * as1->getComponent<Generations>()->getGeneration(), 10.0f + 5.0f * as1->getComponent<Generations>()->getGeneration(), 0);
		as2->addComponent<Transform>(pos2, vel, 10.0f + 5.0f * as1->getComponent<Generations>()->getGeneration(), 10.0f + 5.0f * as1->getComponent<Generations>()->getGeneration(), 0);

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