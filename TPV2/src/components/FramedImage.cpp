#include "FramedImage.h"
#include "../ecs/Entity.h"
FramedImage::~FramedImage() {

}

void FramedImage::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}
void FramedImage::render() {
	SDL_Rect dest = build_sdlrect(tr_->getPos(),
		tr_->getW(),
		tr_->getH());
	tex_->renderFrame(dest, row, col);
}
