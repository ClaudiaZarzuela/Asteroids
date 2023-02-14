#pragma once
#include <vector>
#include <array>

namespace ecs {
	class Component;
	class Entity;
	class Manager {
	public:
		Manager();
		virtual ~Manager();
		Entity* addEntity();
		void refresh();
		void update();
		void render();
	private:
		std::vector<Entity*> ents_;
	
	};
}
