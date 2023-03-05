#include "../checkML.h"
#include "ShowAtOppositeSide.h"
#include "../ecs/Entity.h"

void ShowAtOppositeSide::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}
ShowAtOppositeSide::~ShowAtOppositeSide() {

}

void ShowAtOppositeSide::update() {
	if (tr_->getPos().getX() > sdlutils().width()) {
		tr_->setPos(Vector2D(0 - tr_->getW(), tr_->getPos().getY()));
	}
	else if (tr_->getPos().getX() < 0 - tr_->getW()) {
		tr_->setPos(Vector2D(sdlutils().width(), tr_->getPos().getY()));
	}

	if (tr_->getPos().getY() > sdlutils().height()) {
		tr_->setPos(Vector2D(tr_->getPos().getX(), 0 - tr_->getH()));
	}
	else if (tr_->getPos().getY() < 0- tr_->getH()) {
		tr_->setPos(Vector2D(tr_->getPos().getX(), sdlutils().height()));
	}
}