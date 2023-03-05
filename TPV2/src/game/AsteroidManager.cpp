#include "../checkML.h"
#include "AsteroidManager.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"
#include "../../states/GameOverState.h"
#include "../components/Follow.h"
#include "Game.h"

// metodo encargado de crear un numero definido de asteroides en posiciones random a lo largo de los bordes de la pantalla
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
		as->addComponent<Generations>(sdlutils().rand().nextInt(1, 4));
		as->addComponent<Transform>(p, v, 10.0f + 5.0f* as->getComponent<Generations>()->getGeneration(), 10.0f + 5.0f * as->getComponent<Generations>()->getGeneration(), 0);
		as->addComponent<ShowAtOppositeSide>();
		if (sdlutils().rand().nextInt(0, 10) < 3) {
			as->addComponent<Follow>();
			as->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID_GOLD));
		}
		else { as->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID)); }
	}
	currAsteroids += numAst;
}

// metodo encargado de añadir un nuevo asteroide al juego de forma aleatoria cada periodo determinado de tiempo
void AsteroidManager::addAsteroidFrequently() {
	if (sdlutils().currRealTime() - elapsedTime > 5000) {
		createAsteroids(1);
		elapsedTime = sdlutils().currRealTime();
	}
}

// metodos+ encargado de destruir todos los asteroides
void AsteroidManager::destroyAllAsteroids() {
	for (auto it = mngr_->getEntities(ecs::_grp_ASTEROIDS).begin(); it != mngr_->getEntities(ecs::_grp_ASTEROIDS).end(); ++it) {
		(*it)->setAlive(false);
	}
	currAsteroids = 0;
}

// metodo al que se llama cuando un asteroide colisiona con una bala y que determina si este deberia o no dividirse de acuerdo a su num de generaciones y al num total de asteroides
void AsteroidManager::onCollision(Entity* a) {
	currAsteroids--;
    if (a->getComponent<Generations>()->getGeneration() > 1 && currAsteroids < 30) { 
		Divide(a);
	}
	a->setAlive(false);
}

// metodo encargado de generar dos nuevos asteroides despues de haber destruido a otro, con una generacion menos y una pos, vel y rot aleatorias
void AsteroidManager::Divide(Entity* a) {
	auto r1 = sdlutils().rand().nextInt(0, 360);
	auto pos1 = a->getComponent<Transform>()->getPos() + a->getComponent<Transform>()->getVel().rotate(r1) * 2 * max(a->getComponent<Transform>()->getW(), a->getComponent<Transform>()->getH());
	auto vel1 = a->getComponent<Transform>()->getVel().rotate(r1) * 1.1f;

	auto r2 = sdlutils().rand().nextInt(0, 360);
	auto pos2 = a->getComponent<Transform>()->getPos() + a->getComponent<Transform>()->getVel().rotate(r2) * 2 * max(a->getComponent<Transform>()->getW(), a->getComponent<Transform>()->getH());
	auto vel2 = a->getComponent<Transform>()->getVel().rotate(r2) * 1.1f;

	Entity* as1 = mngr_->addEntity(ecs::_grp_ASTEROIDS); Entity* as2 = mngr_->addEntity(ecs::_grp_ASTEROIDS);
	as1->addComponent<Generations>(a->getComponent<Generations>()->getGeneration() - 1);
	as2->addComponent<Generations>(a->getComponent<Generations>()->getGeneration() - 1);

	as1->addComponent<Transform>(pos1, vel1, 10.0f + 5.0f * as1->getComponent<Generations>()->getGeneration(), 10.0f + 5.0f * as1->getComponent<Generations>()->getGeneration(), 0);
	as2->addComponent<Transform>(pos2, vel2, 10.0f + 5.0f * as1->getComponent<Generations>()->getGeneration(), 10.0f + 5.0f * as1->getComponent<Generations>()->getGeneration(), 0);

	as1->addComponent<ShowAtOppositeSide>();
	as2->addComponent<ShowAtOppositeSide>();

	if (a->hasComponent<Follow>()) {
		as1->addComponent<Follow>();
		as2->addComponent<Follow>();

		as1->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID_GOLD));
		as2->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID_GOLD));
	}
	else { as1->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID)); as2->addComponent<FramedImage>(Game::instance()->getTexture(ASTEROID)); }
	currAsteroids += 2;
}