#include "FighterSystem.h"
#include "../components/Health.h"
#include "../sdlutils/InputHandler.h"
// Crear la entidad del caza, añadir sus componentes, asociarla con un handler
// correspondiente, etc.
void FighterSystem::initSystem() {
	Entity* fighter = mngr_->addEntity(ecs::_grp_GENERAL);
	mngr_->setHandler(ecs::FIGHTER, fighter);
	mngr_->addComponent<Transform>(fighter, Vector2D(sdlutils().width() / 2 - 25, sdlutils().height() / 2), Vector2D(0, 0), 50, 50, 0);
	mngr_->addComponent<Health>(fighter, 3);
	
	tr_ = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::FIGHTER));
}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void FighterSystem::recieve(const ecs::Message& m) {
	switch (m.id)
	{
	case ecs::_m_FIGHTER_CRASHED:
		onCollision_FighterAsteroid(); break;
	case ecs::_m_ROUND_OVER:
		onRoundOver(); break;
	case ecs::_m_ROUND_START:
		onRoundStart(); break;
	default:
		break;
	}
}

// Si el juego está parado no hacer nada, en otro caso actualizar la velocidad
// del caza y moverlo como en la práctica 1 (acelerar, desacelerar, etc). Además, 
// si el juego no está parado y el jugador pulsa la tecla de disparo, enviar un
// mensaje con las características físicas de la bala. Recuerda que se puede disparar
// sólo una bala cada 0.25sec.
void FighterSystem::update() {
	if (active_) {
		if (InputHandler::instance()->isKeyDown(SDLK_UP)) {
			sdlutils().soundEffects().at("thrust").play();
			const float speedLimit = 3.0f;
			Vector2D newVel = tr_->getVel() + Vector2D(0, -1).rotate(tr_->getRot()) * 0.2f;
			if (newVel.magnitude() >= speedLimit) { newVel = newVel.normalize() * speedLimit; }
			tr_->setVel(newVel);
		}

		if (input_->isKeyDown(SDLK_RIGHT)) { tr_->setRot(tr_->getRot() + 5.0f); }
		if (input_->isKeyDown(SDLK_LEFT)) { tr_->setRot(tr_->getRot() - 5.0f); }
		if (input_->isKeyDown(SDLK_s) && shoot) {
			Vector2D bPos = tr_->getPos() + Vector2D(tr_->getW() / 2.0f, tr_->getH() / 2.0f)
				- Vector2D(0.0f, tr_->getH() / 2.0f + 5.0f + 12.0f).rotate(tr_->getRot()) - Vector2D(2.0f, 10.0f);
			Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(tr_->getRot()) * (tr_->getVel().magnitude() + 5.0f);
			double bRot = tr_->getRot(); int bWidth = 5; int bHeight = 20;

			ecs::Message m; m.id = ecs::_m_SHOOT; m.bullet_data.pos = bPos; m.bullet_data.vel = bVel;
			m.bullet_data.rot = bRot; m.bullet_data.width = bWidth; m.bullet_data.height = bHeight;
			mngr_->send(m, true);
			shoot = false;
			elapsedTime = sdlutils().currRealTime();
		}
		if (sdlutils().currRealTime() - elapsedTime > 250) { shoot = true; }
		if (tr_->getVel().magnitude() < 0.05f) { tr_->setVel(Vector2D(0, 0)); }
		else tr_->setVel(tr_->getVel() * 0.995f);
		tr_->setPos(tr_->getPos() + tr_->getVel());

		if (tr_->getPos().getX() > sdlutils().width()) { tr_->setPos(Vector2D(0 - tr_->getW(), tr_->getPos().getY())); }
		else if (tr_->getPos().getX() < 0 - tr_->getW()) { tr_->setPos(Vector2D(sdlutils().width(), tr_->getPos().getY())); }
		if (tr_->getPos().getY() > sdlutils().height()) { tr_->setPos(Vector2D(tr_->getPos().getX(), 0 - tr_->getH())); }
		else if (tr_->getPos().getY() < 0 - tr_->getH()) { tr_->setPos(Vector2D(tr_->getPos().getX(), sdlutils().height())); }
	}
}
// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotación 0. No
// hace falta desactivar la entidad (no dibujarla si el juego está parado).
void FighterSystem::onCollision_FighterAsteroid() {
	tr_->reset();
}
// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
void FighterSystem::onRoundOver() {
	active_ = false;
}
// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
void FighterSystem::onRoundStart() {
	active_ = true;
}