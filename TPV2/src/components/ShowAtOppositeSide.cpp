#include "../checkML.h"
#include "ShowAtOppositeSide.h"

// destructora
ShowAtOppositeSide::~ShowAtOppositeSide() {}

// inicializa las referencias a otros componentes
void ShowAtOppositeSide::initComponent() {
	/*tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);*/
}

// comprueba constantemente la posicion de la nave para trasladarla en cuanto salga de los limites de la pantalla
//void ShowAtOppositeSide::update() {
//	if (tr_->getPos().getX() > sdlutils().width()) {
//		tr_->setPos(Vector2D(0 - tr_->getW(), tr_->getPos().getY()));
//	}
//	else if (tr_->getPos().getX() < 0 - tr_->getW()) {
//		tr_->setPos(Vector2D(sdlutils().width(), tr_->getPos().getY()));
//	}
//
//	if (tr_->getPos().getY() > sdlutils().height()) {
//		tr_->setPos(Vector2D(tr_->getPos().getX(), 0 - tr_->getH()));
//	}
//	else if (tr_->getPos().getY() < 0- tr_->getH()) {
//		tr_->setPos(Vector2D(tr_->getPos().getX(), sdlutils().height()));
//	}
//}