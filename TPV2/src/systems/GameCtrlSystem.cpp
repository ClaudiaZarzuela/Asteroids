#include "GameCtrlSystem.h"

//void GameCtrlSystem::recieve(const ecs::Message& m) {
//	switch (m.id) {
//	case ecs::_m_STAR_EATEN: score_ += 1; break;
//	default: break;
//	}
//}

/*if (input_->isKeyDown(SDLK_UP)) {
		sdlutils().soundEffects().at("thrust").play();
		const float speedLimit = 3.0f;
		Vector2D newVel = tr_->getVel() + Vector2D(0, -1).rotate(tr_->getRot()) * 0.2f;
		if (newVel.magnitude() >= speedLimit) {
			newVel = newVel.normalize()* speedLimit;
		}
		tr_->setVel(newVel);
	}
	if (input_->isKeyDown(SDLK_RIGHT)) {
		tr_->setRot(tr_->getRot() + 5.0f);
	}
	if (input_->isKeyDown(SDLK_LEFT)) {
		tr_->setRot(tr_->getRot() - 5.0f);
	}
	if (input_->isKeyDown(SDLK_s) && shoot) {
		gn_->instanciateBullet();
		shoot = false;
		elapsedTime = sdlutils().currRealTime();
	}
	if (sdlutils().currRealTime() - elapsedTime > 250) {
		shoot = true;
	}*/