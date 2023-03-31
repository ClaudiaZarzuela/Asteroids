#include "../checkML.h"
#include "Manager.h"

Entity* Manager::addEntity(ecs::grpId_type gId) {
	Entity* e = new Entity(gId);
	setAlive(e, true);
	entsByGroup_[gId].push_back(e);
	return e;
}

void Manager::refresh() {
	for (ecs::grpId_type gId = 0; gId < ecs::maxGroupId; ++gId) {
		auto& grpEnts = entsByGroup_[gId];
		grpEnts.erase(
			std::remove_if(grpEnts.begin(), grpEnts.end(), [this](Entity* e) {
				if (isAlive(e)) {
					return false;
				}
				else {
					delete e;
					return true;
				}
				}),
			grpEnts.end());
	}
}

void Manager::update() {
	for (auto sys : sys_) {
		if(sys != nullptr) sys->update();
	}
		   
}

