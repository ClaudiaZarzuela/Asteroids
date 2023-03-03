#pragma once
#include <vector>
#include <array>
#include "Entity.h"
#include "../utils/Singleton.h"

class Manager: public Singleton<Manager> {
	friend Singleton<Manager>;
private:
	std::array<std::vector<Entity*>, ecs::maxGroupId> entsByGroup_;
	Manager(): ents_(), entsByGroup_() {
		for (auto& groupEntities : entsByGroup_) {
			groupEntities.reserve(100);
		}
		ents_.reserve(100);
	};
	std::array<Entity*, ecs::maxHdlrId> hdlrs_;

	std::vector<Entity*> ents_;
public:
	virtual ~Manager(){
		for (auto& ents : entsByGroup_) {
			for (auto e : ents)
				delete e;
}
		for (auto e : ents_) {
			delete e;
		}
	};

	inline void setHandler(ecs::hdlrId_type hId, Entity* e) {
		hdlrs_[hId] = e;
	}

	inline Entity* getHandler(ecs::hdlrId_type hId) {
		return hdlrs_[hId];
	}
	Entity* addEntity(ecs::grpId_type gId = ecs:: _grp_GENERAL);
	void refresh();
	void update();
	void render();
	inline const auto& getEntities() { return ents_; }
	inline const auto& getEntitiesByGroup(ecs::grpId_type gId) {
		return entsByGroup_[gId];
	}
};

