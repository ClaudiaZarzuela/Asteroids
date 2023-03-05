#include "../checkML.h"
#include "FighterCtrl.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

// destructora
FighterCtrl::~FighterCtrl(){}

// inicializa las referencias a otros componentes
void FighterCtrl::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
	gn_ = ent_->getComponent<Gun>();
	assert(gn_ != nullptr);
}

// responde correspondientemente a los inputs detectados, aplicando sus efectos o llamando a otros métodos
void FighterCtrl::handleInput() {
	if (input_->isKeyDown(SDLK_UP)) {
		sdlutils().soundEffects().at("thrust").play();
		const float speedLimit = 3.0f;
		Vector2D newVel = tr_->getVel() + Vector2D(0, -1).rotate(tr_->getRot()) * 0.2f;
		if (newVel.magnitude() >= speedLimit) {
			newVel = newVel.normalize()* speedLimit;
		}
		tr_->setVel(newVel);
	}
	if (input_->isKeyDown(SDLK_RIGHT)) {
		tr_->setRot(tr_->getRot() + 5.0f);
	}
	if (input_->isKeyDown(SDLK_LEFT)) {
		tr_->setRot(tr_->getRot() - 5.0f);
	}
	if (input_->isKeyDown(SDLK_s) && shoot) {
		gn_->instanciateBullet();
		shoot = false;
		elapsedTime = sdlutils().currRealTime();
	}
	if (sdlutils().currRealTime() - elapsedTime > 250) {
		shoot = true;
	}
}