#include "../checkML.h"
#include "DeAcceleration.h"
#include "../ecs/Entity.h"

DeAcceleration::~DeAcceleration() {

}
void DeAcceleration::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}
void DeAcceleration::update() {
	if (tr_->getVel().magnitude() < 0.05f) {
		tr_->setVel(Vector2D(0, 0));
	}
	else tr_->setVel(tr_->getVel() * 0.995f);
}