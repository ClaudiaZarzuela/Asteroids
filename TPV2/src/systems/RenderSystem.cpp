#include "RenderSystem.h"
#include "../components/TextRender.h"
#include "../sdlutils/Texture.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../components/FramedImage.h"
#include "../components/Follow.h"
RenderSystem:: ~RenderSystem() {
	for (int i = 0; i < NUM_TEXTURES; ++i) delete textures[i];
	for (int i = 0; i < NUM_TEXTS; ++i) delete texts[i];
	SDL_DestroyRenderer(renderer);
}
void RenderSystem::recieve(const ecs::Message& m) {
	if (m.id == ecs::_m_CHANGE_STATE) {
		state_ = currentState;
	}
}

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
	//Textos indicativos en cada estado
	//text1_ = mngr_->addEntity(ecs::_grp_TEXT);
	//text2_ = mngr_->addEntity(ecs::_grp_TEXT);
	//mngr_->addComponent<TextRender>(text1_, texts[MAINMENU], (sdlutils().width() - texts[PAUSA]->width()) / 2, ((sdlutils().height() - texts[PAUSA]->height()) / 2) + 100);

}

void RenderSystem::update() {
	auto& sdl = *SDLUtils::instance();
	sdl.clearRenderer();

	//RENDERIZAR LAS VIDAS
	for (int i = 0; i < mngr_->getComponent<Health>(fighter)->getLives(); ++i) {
		Vector2D pos = Vector2D((textures[HEALTH]->width()/3) * i, 0);
		SDL_Rect dest = build_sdlrect(pos, textures[HEALTH]->width()/3, textures[HEALTH]->height()/3);
		textures[HEALTH]->render(dest, 0);
	}

	//RENDERIZA LA NAVE 
	Transform* f = mngr_->getComponent<Transform>(fighter);
	SDL_Rect dest = build_sdlrect(f->getPos(), f->getW(), f->getH());
	textures[NAVE]->render(dest, f->getRot());

	switch (state_) {
		case MAINMENU:
			//RENDER TEXTO
			text1_ = mngr_->addEntity(ecs::_grp_TEXT);
			mngr_->addComponent<TextRender>(text1_, texts[MAINMENU], (sdlutils().width() - texts[PAUSA]->width()) / 2, ((sdlutils().height() - texts[PAUSA]->height()) / 2) + 100)
			; break;

		case PLAY:
			//RENDER TEXTO

			//RENDER BALAS Y ASTEROIDES
			inGameObjects();
			; break;
		case RESTART:
			//RENDER TEXTO
			; break;
		case PAUSE:
			//RENDER TEXTO

			//RENDER BALAS Y ASTEROIDES
			inGameObjects();
			; break;
		case GAMEOVER:
			//RENDER TEXTO
			; break;
	}
	
	//RENDER TEXTOS
	/*for (auto e : mngr_->getEntities(ecs::_grp_TEXT)) {
		if (e != nullptr) {
			TextRender* t = mngr_->getComponent<TextRender>(e);
			if(t != nullptr)
				t->getTexture()->render(t->getPos().getX(), t->getPos().getY());
		}
	}*/
	

	sdl.presentRenderer();
}

void RenderSystem::onRoundStart() {
}

void RenderSystem::onRoundOver() {
}

void RenderSystem::onGameStart() {
}

void RenderSystem::onGameOver() {
}

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