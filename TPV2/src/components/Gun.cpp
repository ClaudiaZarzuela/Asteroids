#include "Gun.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "Image.h"

Gun::~Gun(){

}

void Gun::instanciateBullet() {
	Entity* bullet = mngr_->addEntity(ecs::_grp_BULLETS);
	Vector2D bPos = ent_->getComponent<Transform>()->getPos()
		+ Vector2D(ent_->getComponent<Transform>()->getW() / 2.0f, ent_->getComponent<Transform>()->getH() / 2.0f)
		- Vector2D(0.0f, ent_->getComponent<Transform>()->getH() / 2.0f + 5.0f + 12.0f).rotate(ent_->getComponent<Transform>()->getRot())
		- Vector2D(2.0f, 10.0f);
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(ent_->getComponent<Transform>()->getRot()) * (ent_->getComponent<Transform>()->getVel().magnitude() + 5.0f);
	bullet->addComponent<Transform>(bPos, bVel, 5, 20, ent_->getComponent<Transform>()->getRot()); 
	bullet->addComponent<Image>(game->getTexture(NAVE));

}
void Gun::update() {
	if (shoot && input_->isKeyDown(SDLK_s)) {
		instanciateBullet();
		shoot = false;
		elapsedTime = sdlutils().currRealTime();
	}

	if (elapsedTime > 250) {

	}
}