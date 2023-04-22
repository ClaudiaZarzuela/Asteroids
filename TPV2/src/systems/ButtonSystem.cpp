#include "ButtonSystem.h"

void ButtonSystem::recieve(const ecs::Message& m) {
	switch (m.id)
	{
		case ecs::_m_ONLINE:
			clicked = false;
			createOnlineStateButtons(); break;
		default: break;
	}
}
void ButtonSystem::initSystem() {
	createMainMenuButtons();
}
void ButtonSystem::update() {
	if (active_) {
		vector<Entity*> button = mngr_->getEntities(ecs::_grp_BUTTONS);

		for (int i = 0; i < button.size(); ++i) {
			auto buttonTransform = mngr_->getComponent<Transform>(button[i]);
			SDL_Point mousePosition;
			SDL_Rect buttonRect = { (int)buttonTransform->getPos().getX(), (int)buttonTransform->getPos().getY(), (int)buttonTransform->getW(), (int)buttonTransform->getH() };
			Vector2D position = buttonTransform->getPos();
			SDL_GetMouseState(&mousePosition.x, &mousePosition.y); 
			
			if (SDL_PointInRect(&mousePosition, &buttonRect) && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT) && !clicked) {
				clicked = true;
				auto b = mngr_->getComponent<Button>(button[i]);
				ecs::Message m; 
				switch (b->getID()) {
				case MULTIPLAYER_: m.id = ecs::_m_ONLINE; break;
				case SINGLEPLAYER_: m.id = ecs::_m_SINGLEPLAYER;  break;
					case HOST_: m.id = ecs::_m_HOST; break;
					case CLIENT_: m.id = ecs::_m_CLIENT; break;
				}
				mngr_->send(m, true);
			}
		}
	}

}

void ButtonSystem::createMainMenuButtons() {
	Entity* multi = mngr_->addEntity(ecs::_grp_BUTTONS);
	mngr_->addComponent<Transform>(multi, Vector2D(sdlutils().width() / 2 -75,( sdlutils().height() / 2) -100), Vector2D(0, 0), 150, 100, 0);
	mngr_->addComponent<Button>(multi, MULTIPLAYER_, MULTIPLAYER);

	Entity* solo = mngr_->addEntity(ecs::_grp_BUTTONS);
	mngr_->addComponent<Transform>(solo, Vector2D(sdlutils().width() / 2 - 75, (sdlutils().height() / 2) + 100), Vector2D(0, 0), 150, 100, 0);
	mngr_->addComponent<Button>(solo, SINGLEPLAYER_, SINGLEPLAYER);
}

void ButtonSystem::createOnlineStateButtons() {
	erasePreviousButtons();
	Entity* host = mngr_->addEntity(ecs::_grp_BUTTONS);
	mngr_->addComponent<Transform>(host, Vector2D(sdlutils().width() / 2 - 200, (sdlutils().height() / 2)), Vector2D(0, 0), 150, 100, 0);
	mngr_->addComponent<Button>(host, HOST_, HOST);

	Entity* client = mngr_->addEntity(ecs::_grp_BUTTONS);
	mngr_->addComponent<Transform>(client, Vector2D(sdlutils().width() / 2 +50, (sdlutils().height() / 2)), Vector2D(0, 0), 150, 100, 0);
	mngr_->addComponent<Button>(client, CLIENT_, CLIENT);

}

void ButtonSystem::activateSystem() {
	active_ = true;
}
void ButtonSystem::deactivateSystem() {
	active_ = false;

}

void ButtonSystem::erasePreviousButtons() {
	//Borra los anteriores botones
	for (auto e : mngr_->getEntities(ecs::_grp_BUTTONS)) {
		if (e != nullptr) {
			Button* t = mngr_->getComponent<Button>(e);
			if (t != nullptr)
				mngr_->setAlive(e, false);
		}
	}
}