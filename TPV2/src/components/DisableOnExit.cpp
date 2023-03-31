#include "../checkML.h"
#include "DisableOnExit.h"

// destructora
DisableOnExit:: ~DisableOnExit() {}

// inicializa las referencias a otros componentes
void DisableOnExit::initComponent() {
	/*tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);*/
}

// comprueba constantemente la posicion de la bala para desactivarla en cuanto salga de los limites de la pantalal
//void DisableOnExit::update() {
//
//	if (tr_->getPos().getX() > sdlutils().width() || tr_->getPos().getX() < 0 - tr_->getW() ||
//		tr_->getPos().getY() > sdlutils().height() || tr_->getPos().getY() < 0 - tr_->getH()) {
//		ent_->setAlive(false);
//	}
//}
