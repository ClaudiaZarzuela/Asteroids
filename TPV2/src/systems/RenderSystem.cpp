#include "RenderSystem.h"
#include "../components/TextRender.h"
#include "../sdlutils/Texture.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../components/FramedImage.h"
#include "../components/Follow.h"
#include "../checkML.h"
#include "OnlineSystem.h"

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

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void RenderSystem::recieve(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_PLAY: 
		state_ = PLAY;
		break;

	case ecs::_m_MAINMENU: //pasa al endState
		state_ = MENU;
		break;

	case ecs::_m_RESTART: //pasa al endState
		state_ = RESTART;
		break;

	case ecs::_m_PAUSE: //pasa al pauseState
		state_ = PAUSE;
		break;

	case ecs::_m_GAME_OVER_WIN: //pasa al playState
		state_ = GAMEOVERWIN;
		break;
	case ecs::_m_GAME_OVER_LOSE: //pasa al playState
		state_ = GAMEOVERLOSE;
		break;

	case ecs::_m_WAITING:
		state_ = WAITING;
		break;
	case ecs::_m_START_ONLINE_ROUND:
		state_ = ONLINE;
		break;
	case ecs::_m_NAMES_PLAYERS:
		createNames();
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

	fighter = mngr_->getHandler(ecs::FIGHTER);
	changeText();
}

// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
// - Dibujar las vidas (siempre).
// - Dibujar los mensajes correspondientes: si el juego está parado, etc (como en la práctica 1)
void RenderSystem::update() {
	auto& sdl = *SDLUtils::instance();
	sdl.clearRenderer();

	if (state_ == PLAY) {
		player();
		animateAsteroids();
		inGameObjects();
	}
	else if (state_ == GAMEMODE) {
		//RENDERIZA LOS BOTONES
		auto& grpB = mngr_->getEntities(ecs::_grp_BUTTONS);
		for (auto i = 0; i < grpB.size(); i++)
		{
			Transform* tr_ = mngr_->getComponent<Transform>(grpB[i]);
			int text_ = mngr_->getComponent<Button>(grpB[i])->getTexture();
			SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
			textures[text_]->render(dest, tr_->getRot());

		}
	}
	else if (state_ == ONLINE) {
		playersOnline();
	}
	else {
		player();
		//RENDER TEXTOS
		if (state_ == PAUSA) {
			inGameObjects();
		}
		for (auto e : mngr_->getEntities(ecs::_grp_TEXT)) {
			if (e != nullptr) {
				TextRender* t = mngr_->getComponent<TextRender>(e);
				if (t != nullptr)
					t->getTexture()->render(t->getPos().getX(), t->getPos().getY());
			}
		}
	}
	sdl.presentRenderer();
}

// metodo que renderiza los grupos exclusivos del playstate (asteroides y balas)
void RenderSystem::inGameObjects() {
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
	auto& grpBullets = mngr_->getEntities(ecs::_grp_BULLETS);
	for (auto i = 0; i < grpBullets.size(); i++)
	{
		Transform* tr_ = mngr_->getComponent<Transform>(grpBullets[i]);
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		textures[BULLET]->render(dest, tr_->getRot());
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
		mngr_->addComponent<TextRender>(text1_, texts[PAUSE], (sdlutils().width() - texts[PAUSA]->width()) / 2, ((sdlutils().height() - texts[PAUSA]->height()) / 2) + 100);
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
void RenderSystem::createNames() {
	OnlineSystem* os = mngr_->getSystem<OnlineSystem>();
	ids[0] = new Texture(sdlutils().renderer(), os->getHostName(), sdlutils().fonts().at("ARIAL24"), SDL_Color());
	ids[1] = new Texture(sdlutils().renderer(), os->getClientName(), sdlutils().fonts().at("ARIAL24"), SDL_Color());
}