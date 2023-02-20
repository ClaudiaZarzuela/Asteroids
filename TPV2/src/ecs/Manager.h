#pragma once
#include <vector>
#include <array>
#include "Entity.h"

class Manager {
public:
	Manager(): ents_(){
		ents_.reserve(100);
	};
	virtual ~Manager(){
		for (auto e : ents_) {
			delete e;
		}
	};
	Entity* addEntity();
	void refresh();
	void update();
	void render();
private:
	std::vector<Entity*> ents_;
	
};

