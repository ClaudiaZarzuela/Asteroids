#include "ButtonSystem.h"

void ButtonSystem::recieve(const ecs::Message& m) {
	switch (m.id)
	{
		//llamado para crear los botones de singleplayer y multiplayer
		//tambien activa el sistema
		case ecs::_m_GAMEMODE:
			createMainMenuButtons(); 
			activateSystem();
			break;

		//llamado para crear los botones de host y client
		case ecs::_m_ONLINE:
			clicked = false;
			createOnlineStateButtons(); break;

		//desactiva el sistema cuando empieza una partida, ya sea multiplayer o singleplayer
		case ecs::_m_START_ONLINE_ROUND:
		case ecs::_m_SINGLEPLAYER:
			deactivateSystem();
			break;

		default: break;
	}
}

void ButtonSystem::initSystem() {
	//crea los botones de singleplayer y multiplayer
	createMainMenuButtons();
}

//checkea si se ha pulsado algun boton y si lo ha hecho llamada al metodo correspondiente mediante mensajes
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
				ecs::Message m; 
				m.id = mngr_->getComponent<Button>(button[i])->getFunction();
				mngr_->send(m, true);
			}
		}
	}

}

//crea los botones de singleplayer y multiplayer
void ButtonSystem::createMainMenuButtons() {
	erasePreviousButtons();
	Entity* multi = mngr_->addEntity(ecs::_grp_BUTTONS);
	mngr_->addComponent<Transform>(multi, Vector2D(sdlutils().width() / 2 -75,( sdlutils().height() / 2) -100), Vector2D(0, 0), 150, 100, 0);
	mngr_->addComponent<Button>(multi, MULTIPLAYER, ecs::_m_ONLINE);

	Entity* solo = mngr_->addEntity(ecs::_grp_BUTTONS);
	mngr_->addComponent<Transform>(solo, Vector2D(sdlutils().width() / 2 - 75, (sdlutils().height() / 2) + 100), Vector2D(0, 0), 150, 100, 0);
	mngr_->addComponent<Button>(solo, SINGLEPLAYER, ecs::_m_SINGLEPLAYER);
}

//crea los botones de host y client
void ButtonSystem::createOnlineStateButtons() {
	erasePreviousButtons();
	Entity* host = mngr_->addEntity(ecs::_grp_BUTTONS);
	mngr_->addComponent<Transform>(host, Vector2D(sdlutils().width() / 2 - 200, (sdlutils().height() / 2)), Vector2D(0, 0), 150, 100, 0);
	mngr_->addComponent<Button>(host, HOST, ecs::_m_HOST);

	Entity* client = mngr_->addEntity(ecs::_grp_BUTTONS);
	mngr_->addComponent<Transform>(client, Vector2D(sdlutils().width() / 2 +50, (sdlutils().height() / 2)), Vector2D(0, 0), 150, 100, 0);
	mngr_->addComponent<Button>(client, CLIENT, ecs::_m_CLIENT);

}

//activa el sistema
void ButtonSystem::activateSystem() {
	active_ = true;
	clicked = false;
}

//desactiva el sistema
void ButtonSystem::deactivateSystem() {
	active_ = false;

}

//Borra los anteriores botones para crear nuevos
void ButtonSystem::erasePreviousButtons() {
	for (auto e : mngr_->getEntities(ecs::_grp_BUTTONS)) {
		if (e != nullptr) {
			Button* t = mngr_->getComponent<Button>(e);
			if (t != nullptr)
				mngr_->setAlive(e, false);
		}
	}
}