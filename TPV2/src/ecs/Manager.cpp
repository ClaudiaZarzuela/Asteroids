#include "Manager.h"

	Entity* Manager::addEntity(ecs::grpId_type gId) {
		Entity* e = new Entity();
		e->setAlive(true);
		ents_.push_back(e);
		entsByGroup_[gId].push_back(e);
		return e;
	}

	void Manager::refresh() {
		ents_.erase(
			std::remove_if(ents_.begin(), ents_.end(), [](Entity* e) {
				if (e->isAlive()) {
					return false;
				}
				else {
					delete e;
					return true;
				}
				}), 
			ents_.end());

		for (int i = 0; i < entsByGroup_.size(); i++) {
			entsByGroup_[i].erase(
				std::remove_if(entsByGroup_[i].begin(), entsByGroup_[i].end(), [](Entity* e) {
					if (e->isAlive()) {
						return false;
					}
					else {
						delete e;
						return true;
					}
					}),
				entsByGroup_[i].end());
		}
	}

	void Manager::update() {
		auto n = ents_.size();
		for (auto i = 0u; i < n; i++)
			ents_[i]->update();
	}

	void Manager::render() {
		auto n = ents_.size();
		for (auto i = 0u; i < n; i++)
			ents_[i]->render();
	}
