#pragma once
#include <vector>
#include <array>
#include "Entity.h"
#include "../utils/Singleton.h"

class Manager: public Singleton<Manager> {
	friend Singleton<Manager>;
	Manager(): ents_(){
		ents_.reserve(100);
	};
	std::vector<Entity*> ents_;
public:
	virtual ~Manager(){
		for (auto e : ents_) {
			delete e;
		}
	};
	Entity* addEntity(ecs::grpId_type gId = ecs:: _grp_GENERAL);
	void refresh();
	void update();
	void render();
};

