#include "AsteroidsSystem.h"
#include "../components/Generations.h"
#include "../components/FramedImage.h"
#include "../components/Follow.h"
#include "../game/Game.h"
#include "../components/ShowAtOppositeSide.h"

void AsteroidsSystem::recieve(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_STAR_SHOT:
		onCollision_AsteroidBullet(m.star_eaten_data.e); break;
	case ecs::_m_ADD_STARS:
		addStar(m.add_stars_data.n); break;
	case ecs::_m_ROUND_OVER:
		onRoundOver(); break;
	case ecs::_m_ROUND_START:
		onRoundStart(); break;
	default: break;
	}
}

void AsteroidsSystem::update() {
	for (auto e : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {
		auto tr = mngr_->getComponent<Transform>(e);
		tr->getPos() = tr->getPos() + tr->getVel();
		tr->setRot(tr->getRot() + 5.0f);
	}
}

void AsteroidsSystem::addStar(unsigned int n) {
	for (int i = 0; i < n; ++i) {
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
		mngr_->addComponent<Generations>(as, sdlutils().rand().nextInt(1, 4));
		mngr_->addComponent<Transform>(as, p, v, 10.0f + 5.0f * mngr_->getComponent<Generations>(as)->getGeneration(), 10.0f + 5.0f * mngr_->getComponent<Generations>(as)->getGeneration(), 0);
		mngr_->addComponent<ShowAtOppositeSide>(as);
		if (sdlutils().rand().nextInt(0, 10) < 3) {
			mngr_->addComponent<Follow>(as);
			mngr_->addComponent<FramedImage>(as, Game::instance()->getTexture(ASTEROID_GOLD));
		}
		else { mngr_->addComponent<FramedImage>(as, Game::instance()->getTexture(ASTEROID)); }
	}
	numOfAsteroids_ += n;
}

void AsteroidsSystem::addAsteroidFrequently() {
	if (sdlutils().currRealTime() - elapsedTime > 5000) {
		addStar(1);
		elapsedTime = sdlutils().currRealTime();
	}
}

// metodos+ encargado de destruir todos los asteroides
void AsteroidManager::destroyAllAsteroids() {
	for (auto it = mngr_->getEntities(ecs::_grp_ASTEROIDS).begin(); it != mngr_->getEntities(ecs::_grp_ASTEROIDS).end(); ++it) {
		mngr_->setAlive((*it), false);
	}
	currAsteroids = 0;
}

void AsteroidsSystem::onCollision_AsteroidBullet(Entity* a) {
	if (mngr_->getComponent<Generations>(a)->getGeneration() > 1 && numOfAsteroids_ < 30) {
		for (int i = 0; i < 2; ++i) {
			auto r = sdlutils().rand().nextInt(0, 360);
			auto pos = mngr_->getComponent<Transform>(a)->getPos() + mngr_->getComponent<Transform>(a)->getVel().rotate(r) * 2 * max(mngr_->getComponent<Transform>(a)->getW(), mngr_->getComponent<Transform>(a)->getH());
			auto vel = mngr_->getComponent<Transform>(a)->getVel().rotate(r) * 1.1f;

			Entity* as = mngr_->addEntity(ecs::_grp_ASTEROIDS);
			mngr_->addComponent<Generations>(as, mngr_->getComponent<Generations>(a)->getGeneration() - 1);
			mngr_->addComponent<Transform>(as, pos, vel, 10.0f + 5.0f * mngr_->getComponent<Generations>(as)->getGeneration(), 10.0f + 5.0f * mngr_->getComponent<Generations>(as)->getGeneration(), 0);
			mngr_->addComponent<ShowAtOppositeSide>(as);

			if (mngr_->hasComponent<Follow>(a)) {
				mngr_->addComponent<Follow>(as);
				mngr_->addComponent<FramedImage>(as, Game::instance()->getTexture(ASTEROID_GOLD));
			}
			else {
				mngr_->addComponent<FramedImage>(as, Game::instance()->getTexture(ASTEROID));
			}
		}
		numOfAsteroids_ += 2;
		mngr_->setAlive(a, false);
	}
}

void AsteroidsSystem::onRoundOver() {
	for (auto e : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {
		mngr_->setAlive(e, false);
	}
	active_ = false;
}

void AsteroidsSystem::onRoundStart() {
	active_ = true;
	addStar(10);
}