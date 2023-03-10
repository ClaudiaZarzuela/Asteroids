#include "Image.h"
#include "../ecs/Entity.h"
Image::~Image()
{
}
void Image::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Image::render() {
	SDL_Rect dest = build_sdlrect(tr_->getPos(),
		tr_->getW(),
		tr_->getH());
	tex_->render(dest, tr_->getRot());
}