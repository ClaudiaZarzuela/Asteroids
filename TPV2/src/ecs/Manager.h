#pragma once
#include "../checkML.h"
#include <vector>
#include <array>
#include "Entity.h"

class Manager {
private:
	std::array<std::vector<Entity*>, ecs::maxGroupId> ents_;
	std::array<Entity*, ecs::maxHdlrId> hdlrs_;

public:
	Manager(): ents_(), hdlrs_() {
		for (auto& groupEntities : ents_) {
			groupEntities.reserve(100);
		}
	};

	virtual ~Manager(){
		for (auto& ents : ents_) {
			for (auto e : ents) {
				delete[] e;
				e = nullptr;
			}
		}

		/*for (int i = 0; i < ents_.size(); ++i) {
			for (int j = 0; j < ents_[i].size(); ++j) {
				delete ents_[i][j];
			}
			delete ents_;
		}
		delete[] ents_;*/
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
	void inputHandler();
	inline const auto& getEntities(ecs::grpId_type gId) { return ents_[gId]; }
	
};

