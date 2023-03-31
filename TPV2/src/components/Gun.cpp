#include "Gun.h"
#include "../checkML.h"
#include "Image.h"
#include "DisableOnExit.h"
#include "../sdlutils/SDLUtils.h"

// destructora
Gun::~Gun() {}

// genera una bala con la posicion, velocidad y rotacion correspondientes
void Gun::instanciateBullet() {
	sdlutils().soundEffects().at("fire").play();
	Entity* bullet = mngr_->addEntity(ecs::_grp_BULLETS);
	Vector2D bPos = tr_->getPos()
		+ Vector2D(tr_->getW() / 2.0f, tr_->getH() / 2.0f)
		- Vector2D(0.0f, tr_->getH() / 2.0f + 5.0f + 12.0f).rotate(tr_->getRot())
		- Vector2D(2.0f, 10.0f);
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(tr_->getRot()) * (tr_->getVel().magnitude() + 5.0f);
	mngr_->addComponent<Transform>(bullet, bPos, bVel, 5, 20, tr_->getRot());
	mngr_->addComponent<Image>(bullet,tex_);
	mngr_->addComponent<DisableOnExit>(bullet);

}

// inicializa las referencias a otros componentes
void Gun::initComponent() {
	/*tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);*/
}