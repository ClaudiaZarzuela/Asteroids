#include "../checkML.h"
#include "Follow.h"

// destructora
Follow::~Follow() {}

// inicializa las referencias a otros componentes
void Follow::initComponent() {
	//tr_ = ent_->getComponent<Transform>();
	
	//assert(tr_ != nullptr);
	//q = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::FIGHTER));
}

// actualiza la posicion del ateroide con respecto a la de la nave
//void Follow::update() {
//	tr_->setVel(tr_->getVel().rotate(tr_->getVel().angle(q->getPos() - tr_->getPos()) > 0 ? 1.0f : -1.0f));
//}