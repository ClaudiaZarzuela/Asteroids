#include "RenderSystem.h"
#include "../components/TextRender.h"
#include "../sdlutils/Texture.h"

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

	//Textos indicativos en cada estado
	//text1_ = mngr_->addEntity(ecs::_grp_TEXT);
	//text2_ = mngr_->addEntity(ecs::_grp_TEXT);
	//mngr_->addComponent<TextRender>(text1_, texts[MAINMENU], (sdlutils().width() - texts[PAUSA]->width()) / 2, ((sdlutils().height() - texts[PAUSA]->height()) / 2) + 100);

}

void RenderSystem::update() {
	auto& sdl = *SDLUtils::instance();
	sdl.clearRenderer();

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
	switch (state_) {
	case MAINMENU:

		; break;
	case PLAY:; break;
	case RESTART:; break;
	case PAUSE:; break;
	case GAMEOVER:; break;
	}
}

void RenderSystem::onRoundOver() {
	switch (state_) {
	case MAINMENU:

		; break;
	case PLAY:; break;
	case RESTART:; break;
	case PAUSE:; break;
	case GAMEOVER:; break;
	}
}

void RenderSystem::onGameStart() {
	switch (state_) {
	case MAINMENU:

		; break;
	case PLAY:; break;
	case RESTART:; break;
	case PAUSE:; break;
	case GAMEOVER:; break;
	}
}

void RenderSystem::onGameOver() {
	switch (state_) {
	case MAINMENU:

		; break;
	case PLAY:; break;
	case RESTART:; break;
	case PAUSE:; break;
	case GAMEOVER:; break;
	}
}