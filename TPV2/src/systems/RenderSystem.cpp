#include "RenderSystem.h"
#include "../components/TextRender.h"
#include "../sdlutils/Texture.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../components/FramedImage.h"
#include "../components/Follow.h"
#include "../checkML.h"

// Destructora de la clase
RenderSystem:: ~RenderSystem() {
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		delete textures[i];
		textures[i] = nullptr;
	}
	for (int i = 0; i < NUM_TEXTS; ++i) {
		delete texts[i];
		texts[i] = nullptr;
	}
	SDL_DestroyRenderer(renderer);
}

// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
void RenderSystem::recieve(const ecs::Message& m) {
	//Se cambia de estado dependiendo del mensaje recibido
	switch (m.id) {
	case ecs::_m_GAMEMODE: //estado que muestra los botones correspondientes del main menu
		state_ = GAMEMODE;
		//borra las entidades creadas por el modo multiplayer cada vez que se empieza una nueva partida
		deleteInGameObjects();
		break;

	case ecs::_m_SINGLEPLAYER:
	case ecs::_m_MAINMENU:
		state_ = MENU;
		break;

	case ecs::_m_ROUND_START:  //empieza la partida de sigleplayer
	case ecs::_m_PLAY:
		state_ = PLAY;
		break;

	case ecs::_m_RESTART: 
		state_ = RESTART;
		break;

	case ecs::_m_PAUSE: 
		state_ = PAUSE;
		break;

	case ecs::_m_GAME_OVER_WIN: 
		state_ = GAMEOVERWIN;
		break;
	case ecs::_m_GAME_OVER_LOSE: 
		state_ = GAMEOVERLOSE;
		break;

	case ecs::_m_HOST:
	case ecs::_m_WAITING:
		state_ = WAITING;
		break;

	case ecs::_m_START_ONLINE_ROUND: //empieza la partida de multiplayer
		createNames(m.player_name_data.hostName, m.player_name_data.clientName); //crea los textos de las naves en el modo multiplayer
		state_ = ONLINE;
		break;

	case ecs::_m_ONLINE_OVER: //avisa de que ha acabado de partida multiplayer y muestra el ganador 
		winner = m.player_shot_data.playerWinner;
		state_ = ONLINEOVER;
		break;
	}
	changeText();
}

// Inicializar el sistema, etc.
void RenderSystem::initSystem() {
	auto& sdl = *SDLUtils::instance();
	renderer = sdl.renderer();
	for (int i = 0; i < NUM_TEXTURES; ++i)
	{
		textures[i] = new Texture(renderer, texture[i].filename, texture[i].rows, texture[i].cols);
	}
	for (int i = 0; i < NUM_TEXTS; ++i)
	{
		if (text[i].backgroundColor == 0) {
			texts[i] = new Texture(renderer, text[i].content, sdl.fonts().at("ARIAL24"), build_sdlcolor(text[i].textColor));

		}
		else texts[i] = new Texture(renderer, text[i].content, sdl.fonts().at("ARIAL24"), build_sdlcolor(text[i].textColor), build_sdlcolor(0xffffffff));
	}
	changeText();
}

// - Dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
// - Dibujar las vidas (siempre).
// - Dibujar los mensajes correspondientes: si el juego est� parado, etc (como en la pr�ctica 1)
void RenderSystem::update() {
	auto& sdl = *SDLUtils::instance();
	sdl.clearRenderer();
	switch(state_) {
		case GAMEMODE: menuButtons(); break; //estado que renderiza los botones correspondientes cuando se esta en el main menu
		case WAITING: waitingtext(); break; //renderiza el texto de espera cuando eres host hasta que llegue un cliente
		case ONLINE: playersOnline(); bulletsOnline(); bullets(); break; //renderiza los jugadores y las balas en modo multiplayer
		case PLAY: player(); animateAsteroids(); asteroids(); bullets();  break; // renderiza el jugador, los asteroides (animados) y las balas en modo singleplayer
		case PAUSE: menuTexts(); asteroids(); bullets(); player(); break; //renderiza lo mismo que en el estado de play pero todo pausado
		case ONLINEOVER: menuTexts(); showWinner(); break; // muestra el nombre del ganador del modo multiplayer y un "press to continue"
		case MENU: case RESTART: case GAMEOVERWIN: case GAMEOVERLOSE: menuTexts(); player(); break; //renderiza los textos correspondientes del estado en el que estes y el player
	}
	sdl.presentRenderer();
}

//Crea el rectangulo destino del texto que muestra quien ha ganado tras una partida multiplayer y lo muestra
void RenderSystem::showWinner() {
	SDL_Rect r;
	r.w = ids[winner]->width(); r.h = ids[winner]->height();
	r.x = (sdlutils().width() - ids[winner]->width()) / 2;
	r.y = ((sdlutils().height() - ids[winner]->height()) / 2);
	ids[winner]->render(r);
}


// metodo que renderiza los grupos exclusivos del playstate (asteroides y balas)
void RenderSystem::asteroids() {
	auto& grpAst = mngr_->getEntities(ecs::_grp_ASTEROIDS);
	for (auto i = 0; i < grpAst.size(); i++)
	{
		Transform* tr_ = mngr_->getComponent<Transform>(grpAst[i]);
		int row = mngr_->getComponent<FramedImage>(grpAst[i])->getRow();
		int col = mngr_->getComponent<FramedImage>(grpAst[i])->getCol();
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		if (mngr_->hasComponent<Follow>(grpAst[i]))
			textures[ASTEROID_GOLD]->renderFrame(dest, row, col, tr_->getRot());
		else
			textures[ASTEROID]->renderFrame(dest, row, col, tr_->getRot());
	}
}

//renderiza las balas de tu jugador
void RenderSystem::bullets() {
	auto& grpBullets = mngr_->getEntities(ecs::_grp_BULLETS);
	for (auto i = 0; i < grpBullets.size(); i++)
	{
		Transform* tr_ = mngr_->getComponent<Transform>(grpBullets[i]);
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		textures[BULLET]->render(dest, tr_->getRot());
	}
}

//renderiza las balas del jugador enemigo en una partida multiplayer
void RenderSystem::bulletsOnline() {
	auto& grpBullets = mngr_->getEntities(ecs::_grp_ENEMY_BULLETS);
	for (auto i = 0; i < grpBullets.size(); i++)
	{
		Transform* tr_ = mngr_->getComponent<Transform>(grpBullets[i]);
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		textures[BULLET]->render(dest, tr_->getRot());
	}
}

//renderiza los botones correspondientes dependiendo del menu actual
void RenderSystem::menuButtons() {
	auto& grpB = mngr_->getEntities(ecs::_grp_BUTTONS);
	for (auto i = 0; i < grpB.size(); i++)
	{
		Transform* tr_ = mngr_->getComponent<Transform>(grpB[i]);
		int text_ = mngr_->getComponent<Button>(grpB[i])->getTexture();
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		textures[text_]->render(dest, tr_->getRot());
	}
}

//renderiza el texto de espera cuando eres host hasta que llegue un cliente
void RenderSystem::waitingtext() {
	text1_ = mngr_->addEntity(ecs::_grp_TEXT);
	mngr_->addComponent<TextRender>(text1_, texts[WAIT], (sdlutils().width() - texts[WAIT]->width()) / 2, ((sdlutils().height() - texts[WAIT]->height()) / 2));
	TextRender* t = mngr_->getComponent<TextRender>(text1_);
	t->getTexture()->render(t->getPos().getX(), t->getPos().getY());
}


void RenderSystem::menuTexts() {
	for (auto e : mngr_->getEntities(ecs::_grp_TEXT)) {
		if (e != nullptr) {
			TextRender* t = mngr_->getComponent<TextRender>(e);
			if (t != nullptr)
				t->getTexture()->render(t->getPos().getX(), t->getPos().getY());
		}
	}
}
// metodo que anima los asteroides
void RenderSystem::animateAsteroids() {
	if (sdlutils().currRealTime() >= frameTime) {
		auto& grpAst = mngr_->getEntities(ecs::_grp_ASTEROIDS);
		for (auto i = 0; i < grpAst.size(); i++)
		{
			int row = mngr_->getComponent<FramedImage>(grpAst[i])->getRow();
			int col = mngr_->getComponent<FramedImage>(grpAst[i])->getCol();
			int colTotal = textures[ASTEROID]->getCol();
			int rowTotal = textures[ASTEROID]->getRow();
				
			mngr_->getComponent<FramedImage>(grpAst[i])->setCol((col + 1) % colTotal);

			if (mngr_->getComponent<FramedImage>(grpAst[i])->getCol() == colTotal -1) {
				mngr_->getComponent<FramedImage>(grpAst[i])->setRow((row + 1) % rowTotal);
			}
			frameTime = sdlutils().currRealTime() + 50;
		}
	}
}

// metodo que cambia el texto que se muestra en pantalla en cada estado
void RenderSystem::changeText() {
	for (auto e : mngr_->getEntities(ecs::_grp_TEXT)) {
		if (e != nullptr) {
			TextRender* t = mngr_->getComponent<TextRender>(e);
			if(t != nullptr)
				mngr_->setAlive(e, false);
		}
	}
	if (state_ == MENU) {
		text1_ = mngr_->addEntity(ecs::_grp_TEXT);
		mngr_->addComponent<TextRender>(text1_, texts[MAINMENU], (sdlutils().width() - texts[PAUSA]->width()) / 2, ((sdlutils().height() - texts[PAUSA]->height()) / 2) + 100);
	}
	else {
		text1_ = mngr_->addEntity(ecs::_grp_TEXT); 
		mngr_->addComponent<TextRender>(text1_, texts[PAUSA], (sdlutils().width() - texts[PAUSA]->width()) / 2, ((sdlutils().height() - texts[PAUSA]->height()) / 2) + 100);
		if (state_ == GAMEOVERLOSE) {
			text2_ = mngr_->addEntity(ecs::_grp_TEXT);
			mngr_->addComponent<TextRender>(text2_, texts[LOSE], (sdlutils().width()- texts[LOSE]->width()) / 2, ((sdlutils().height() - texts[PAUSA]->height()) / 2) -100);
		}
		else if (state_ == GAMEOVERWIN) {
			text2_ = mngr_->addEntity(ecs::_grp_TEXT);
			mngr_->addComponent<TextRender>(text2_, texts[WIN], (sdlutils().width() - texts[WIN]->width()) / 2, ((sdlutils().height() - texts[PAUSA]->height()) / 2) - 100);
		}
	}
}

void RenderSystem::player() {
	fighter = mngr_->getHandler(ecs::FIGHTER);
	if (fighter != nullptr) {
		//RENDERIZAR LAS VIDAS
		for (int i = 0; i < mngr_->getComponent<Health>(fighter)->getLives(); ++i) {
			Vector2D pos = Vector2D((textures[HEALTH]->width() / 3) * i, 0);
			SDL_Rect dest = build_sdlrect(pos, textures[HEALTH]->width() / 3, textures[HEALTH]->height() / 3);
			textures[HEALTH]->render(dest, 0);
		}
		//RENDERIZA LA NAVE 
		Transform* f = mngr_->getComponent<Transform>(fighter);
		SDL_Rect dest = build_sdlrect(f->getPos(), f->getW(), f->getH());
		textures[NAVE]->render(dest, f->getRot());
	}
}

void RenderSystem::playersOnline() {
	auto& grpPlayers = mngr_->getEntities(ecs::_grp_PLAYERS);
	for (auto i = 0; i < grpPlayers.size(); i++)
	{
		Transform* f = mngr_->getComponent<Transform>(grpPlayers[i]);
		SDL_Rect dest = build_sdlrect(f->getPos(), f->getW(), f->getH());
		textures[NAVE]->render(dest, f->getRot());

		for (int j = 0; j < mngr_->getComponent<Health>(grpPlayers[i])->getLives(); ++j) {
			Vector2D pos = Vector2D((textures[HEALTH]->width() / 3) * j, i * 50);
			SDL_Rect dest = build_sdlrect(pos, textures[HEALTH]->width() / 3, (textures[HEALTH]->height() / 3));
			textures[HEALTH]->render(dest, 0);
		}

		if (ids[i] != nullptr) {
			SDL_Rect r;
			r.w = ids[i]->width(); r.h = ids[i]->height();
			r.x = f->getPos().getX() + f->getW()/2 - r.w /2; r.y = f->getPos().getY() + f->getH();
			ids[i]->render(r);
		}
	}
}
void RenderSystem::createNames(std::string p1, std::string p2) {
	ids[0] = new Texture(sdlutils().renderer(), p1, sdlutils().fonts().at("ARIAL24"), SDL_Color());
	ids[1] = new Texture(sdlutils().renderer(), p2, sdlutils().fonts().at("ARIAL24"), SDL_Color());

	std::string won1 = p1 + " WON!";
	std::string won2 = p2 + " WON!";
	ids[2] = new Texture(sdlutils().renderer(), won1, sdlutils().fonts().at("ARIAL24"), SDL_Color());
	ids[3] = new Texture(sdlutils().renderer(), won2, sdlutils().fonts().at("ARIAL24"), SDL_Color());

}

void RenderSystem::deleteInGameObjects() {
	for (auto e : mngr_->getEntities(ecs::_grp_ENEMY_BULLETS)) {
		mngr_->setAlive(e, false);
	}
	for (auto e : mngr_->getEntities(ecs::_grp_PLAYERS)) {
		mngr_->setAlive(e, false);
	}
}