#include "DisableOnExit.h"
#include "../ecs/Entity.h"

void DisableOnExit::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void DisableOnExit::update() {
	if (tr_->getPos().getX() > sdlutils().width() || tr_->getPos().getX() < 0 - tr_->getW() ||
		tr_->getPos().getY() > sdlutils().height() || tr_->getPos().getY() < 0 - tr_->getH()) {
		ent_->setAlive(false);
	}
	
}