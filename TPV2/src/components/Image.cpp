#include "../checkML.h"
#include "Image.h"
#include "../ecs/Entity.h"

// destructora
Image::~Image() {}

// inicializa las referencias a otros componentes
void Image::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

// renderiza la textura
void Image::render() {
	SDL_Rect dest = build_sdlrect(tr_->getPos(),
		tr_->getW(),
		tr_->getH());
	tex_->render(dest, tr_->getRot());
}