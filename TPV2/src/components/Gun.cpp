#include "Gun.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Image.h"
#include "DisableOnExit.h"
#include "../sdlutils/SDLUtils.h"

Gun::~Gun(){

}

void Gun::instanciateBullet() {
	sdlutils().soundEffects().at("fire").play();
	Entity* bullet = mngr_->addEntity(ecs::_grp_BULLETS);
	Vector2D bPos = tr_->getPos()
		+ Vector2D(tr_->getW() / 2.0f, tr_->getH() / 2.0f)
		- Vector2D(0.0f, tr_->getH() / 2.0f + 5.0f + 12.0f).rotate(tr_->getRot())
		- Vector2D(2.0f, 10.0f);
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(tr_->getRot()) * (tr_->getVel().magnitude() + 5.0f);
	bullet->addComponent<Transform>(bPos, bVel, 5, 20, tr_->getRot());
	bullet->addComponent<Image>(tex_);
	bullet->addComponent<DisableOnExit>();

}
void Gun::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}