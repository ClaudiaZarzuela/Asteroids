#include "GameCtrlSystem.h"

void GameCtrlSystem::recieve(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_STAR_SHOT: score_ += 1; break;
	default: break;
	}
}

void GameCtrlSystem::update() {
	if (input_->isKeyDown(SDLK_UP)) {
		sdlutils().soundEffects().at("thrust").play();
		ecs::Message m; m.id = ecs::_m_UP;
		mngr_->send(m, true);
		/*const float speedLimit = 3.0f;
		Vector2D newVel = tr_->getVel() + Vector2D(0, -1).rotate(tr_->getRot()) * 0.2f;
		if (newVel.magnitude() >= speedLimit) {
			newVel = newVel.normalize() * speedLimit;
		}
		tr_->setVel(newVel);*/
	}
	if (input_->isKeyDown(SDLK_RIGHT)) {
		ecs::Message m; m.id = ecs::_m_RIGHT;
		mngr_->send(m, true);
		//tr_->setRot(tr_->getRot() + 5.0f);
	}
	if (input_->isKeyDown(SDLK_LEFT)) {
		ecs::Message m; m.id = ecs::_m_LEFT;
		mngr_->send(m, true);
		//tr_->setRot(tr_->getRot() - 5.0f);
	}
	if (input_->isKeyDown(SDLK_s) && shoot) {
		//gn_->instanciateBullet();
		ecs::Message m; m.id = ecs::_m_SHOOT;
		mngr_->send(m, true);
		shoot = false;
		elapsedTime = sdlutils().currRealTime();
	}
	if (sdlutils().currRealTime() - elapsedTime > 250) {
		shoot = true;
	}
}