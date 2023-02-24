#include "Gun.h"
#include "../ecs/Entity.h"

Gun::~Gun() {

}

void Gun::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Gun::update() {
	if (input_->isKeyDown(SDLK_s)) {
		
		sdlutils().currTime()

	}
}