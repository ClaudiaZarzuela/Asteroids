#include "RenderSystem.h"
#include "../components/TextRender.h"
#include "../sdlutils/Texture.h"
void RenderSystem::recieve(const ecs::Message& m) {
	if (m.id == ecs::_m_CHANGE_STATE) {
		state_ = currentState;
	}
}

void RenderSystem::initSystem() {
	//Textos indicativos en cada estado
	text1_ = mngr_->addEntity(ecs::_grp_TEXT);
	//text2_ = mngr_->addEntity(ecs::_grp_TEXT);
	mngr_->addComponent<TextRender>(text1_, Game::instance()->getText(MAINMENU), (sdlutils().width() - Game::instance()->getText(PAUSA)->width()) / 2, ((sdlutils().height() - Game::instance()->getText(PAUSA)->height()) / 2) + 100);

}

void RenderSystem::update() {
	for (auto e : mngr_->getEntities(ecs::_grp_TEXT)) {
		if (e != nullptr) {
			TextRender* t = mngr_->getComponent<TextRender>(e);
			t->getTexture()->render(t->getPos().getX(), t->getPos().getY());
		}
	}
	/*if (state_ == PLAY) {

	}
	else {
		mngr_->getComponent<TextRender>(text1_)->getTexture1()->render(mngr_->getComponent<TextRender>(text1_)->getPos().getX(), mngr_->getComponent<TextRender>(text1_)->getPos().getY());
		if (text2_ != nullptr) {
			mngr_->getComponent<TextRender>(text2_)->getTexture1()->render(mngr_->getComponent<TextRender>(text2_)->getPos().getX(), mngr_->getComponent<TextRender>(text2_)->getPos().getY());
		}
	}*/
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