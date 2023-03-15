#include "AsteroidsSystem.h"

void AsteroidsSystem::recieve(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_STAR_EATEN:
		onStarEaten(m.star_eaten_data.e); break;
	case ecs::_m_ADD_STARS:
		addStar(m.create_stars_data.n); break;
	default: break;
	}
}