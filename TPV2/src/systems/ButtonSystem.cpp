#include "ButtonSystem.h"

void ButtonSystem::recieve(const ecs::Message& m) {
	switch (m.id)
	{
		case ecs::_m_GAMEMODE:
			createMainMenuButtons(); break;
		case ecs::_m_ONLINE:
			createOnlineStateButtons(); break;
	
		default: break;
	}
}

void ButtonSystem::initSystem() { 

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
			
			if (SDL_PointInRect(&mousePosition, &buttonRect) && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) { 
				auto b = mngr_->getComponent<Button>(button[i]);
				switch (b->getID()) {
					case MULTIPLAYER_: std::cout << "Multiplayer" << endl; break;
					case SINGLEPLAYER_: std::cout << "Multiplayer" << endl; break;
					case HOST_:std::cout << "Multiplayer" << endl; break;
					case CLIENT_: std::cout << "Multiplayer" << endl; break;
				}
			}
		}
	}

}

void ButtonSystem::createMainMenuButtons() {
	Entity* multi = mngr_->addEntity(ecs::_grp_BUTTONS);
	mngr_->addComponent<Transform>(multi, Vector2D(sdlutils().width() / 2 - 25, sdlutils().height() / 2), Vector2D(0, 0), 50, 50, 0);
	mngr_->addComponent<Button>(multi, MULTIPLAYER_);

	Entity* solo = mngr_->addEntity(ecs::_grp_BUTTONS);
	mngr_->addComponent<Transform>(solo, Vector2D(sdlutils().width() / 2 - 25, sdlutils().height() / 2), Vector2D(0, 0), 50, 50, 0);
	mngr_->addComponent<Button>(solo, SINGLEPLAYER_);
}

void ButtonSystem::createOnlineStateButtons() {
	Entity* host = mngr_->addEntity(ecs::_grp_BUTTONS);
	mngr_->addComponent<Transform>(host, Vector2D(sdlutils().width() / 2 - 25, sdlutils().height() / 2), Vector2D(0, 0), 50, 50, 0);
	mngr_->addComponent<Button>(host, HOST_);

	Entity* client = mngr_->addEntity(ecs::_grp_BUTTONS);
	mngr_->addComponent<Transform>(client, Vector2D(sdlutils().width() / 2 - 25, sdlutils().height() / 2), Vector2D(0, 0), 50, 50, 0);
	mngr_->addComponent<Button>(client, CLIENT_);
}