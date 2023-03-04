#include "Health.h"
#include "../ecs/Entity.h"
Health::~Health() {

}

void Health::render() {
	for (int i = 0; i < actLives; ++i) {
		tex_->render(tex_->width()*i, 0);
	}
}