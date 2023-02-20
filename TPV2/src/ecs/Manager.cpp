#include "Manager.h"

	Entity* Manager::addEntity() {
		Entity* e = new Entity();
		e->setAlive(true);
		e->setContext(this);
		ents_.push_back(e);
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
				}), //
			ents_.end());
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
