#include "GameCtrlSystem.h"

void GameCtrlSystem::recieve(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_STAR_EATEN: score_ += 1; break;
	default: break;
	}
}
