#include "Health.h"
#include "../ecs/Entity.h"
Health::~Health() {

}

void Health::render() {
	SDL_Rect destRect;
	destRect.w = textSize; destRect.h = textSize;
	destRect.x = 0; destRect.y = 0;
	for (int i = 0; i < actLives; ++i) {
		tex_->render(destRect);
		destRect.x += textSize;
	}
}