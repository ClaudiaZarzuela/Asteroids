#include "../checkML.h"
#include "FramedImage.h"

// destructora
FramedImage::~FramedImage() {}

// inicializa las referencias a otros componentes
void FramedImage::initComponent() {
//	tr_ = ent_->getComponent<Transform>();
//	assert(tr_ != nullptr);
}

//// renderiza la textura
//void FramedImage::render() {
//	SDL_Rect dest = build_sdlrect(tr_->getPos(),
//		tr_->getW(),
//		tr_->getH());
//	tex_->renderFrame(dest, row, col, tr_->getRot());
//}

// actualiza las filas y columnas de la textura para cambiar el frame de la animacion
//void FramedImage::update() {
//	if (sdlutils().currRealTime() >= frameTime) {
//		col = (col + 1) % tex_->getCol();
//
//		if (col == tex_->getCol()) {
//			row = (row + 1) % tex_->getRow();
//		}
//		frameTime = sdlutils().currRealTime() + 50;
//	}
//}