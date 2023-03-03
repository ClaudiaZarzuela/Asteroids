#pragma once
#include <vector>
#include <array>
#include "Entity.h"
#include "../utils/Singleton.h"

class Manager: public Singleton<Manager> {
	friend Singleton<Manager>;
private:
	std::array<std::vector<Entity*>, ecs::maxGroupId> ents_;
	std::array<Entity*, ecs::maxHdlrId> hdlrs_;
	Manager(): ents_(), hdlrs_() {
		for (auto& groupEntities : ents_) {
			groupEntities.reserve(100);
		}
	};

public:
	virtual ~Manager(){
		for (auto& ents : ents_) {
			for (auto e : ents)
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
	inline const auto& getEntities(ecs::grpId_type gId) { return ents_[gId]; }
	
};

