#include "Manager.h"

	Entity* Manager::addEntity(ecs::grpId_type gId) {
		Entity* e = new Entity(this);
		e->setAlive(true);
		ents_[gId].push_back(e);
		return e;
	}

	void Manager::refresh() {
		for (ecs::grpId_type gId = 0; gId < ecs::maxGroupId; ++gId) {
			auto& grpEnts = ents_[gId];
			grpEnts.erase(
				std::remove_if(grpEnts.begin(), grpEnts.end(), [](Entity* e) {
					if (e->isAlive()) {
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
		for (auto& ents : ents_) {
			auto n = ents.size();
			for (auto i = 0u; i < n; i++)
				ents[i]->update();
		}
		   
	}

	void Manager::render() {
		for (auto& ents : ents_) {
			auto n = ents.size();
			for (auto i = 0u; i < n; i++)
				ents[i]->render();
		}
	}
