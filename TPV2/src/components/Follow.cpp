#include "../checkML.h"
#include "Follow.h"
#include "../ecs/Manager.h"

Follow::~Follow() {

}
void Follow::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
	q = mngr_->getHandler(ecs::FIGHTER)->getComponent<Transform>();
}

void Follow::update() {
	tr_->setVel(tr_->getVel().rotate(tr_->getVel().angle(q->getPos() - tr_->getPos()) > 0 ? 1.0f : -1.0f));
}