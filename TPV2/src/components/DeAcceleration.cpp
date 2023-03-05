#include "../checkML.h"
#include "DeAcceleration.h"
#include "../ecs/Entity.h"

// destructora
DeAcceleration::~DeAcceleration() {}

// inicializa las referencias a otros componentes
void DeAcceleration::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

// actualiza la velocidad del cada por una menor a cada llamada del bucle
void DeAcceleration::update() {
	if (tr_->getVel().magnitude() < 0.05f) {
		tr_->setVel(Vector2D(0, 0));
	}
	else tr_->setVel(tr_->getVel() * 0.995f);
}