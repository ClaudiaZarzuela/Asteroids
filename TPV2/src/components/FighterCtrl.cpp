#include "FighterCtrl.h"
#include "../ecs/Entity.h"
FighterCtrl::~FighterCtrl(){}

void FighterCtrl::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}
void FighterCtrl::update() {
	if (input_->isKeyDown(SDLK_UP)) {
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
}