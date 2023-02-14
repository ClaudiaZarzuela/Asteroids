#pragma once
#include "../game/ecs_def.h"

namespace ecs {
	class Component;
	class Manager;
	class Entity {
	public:

		template<typename T>
		inline void removeComponent(cmpId_type cId) {
			constexpr cmpId_type cId = T::id;
			//...
		}

		template<typename T>
		inline T* getComponent(cmpId_type cId) {
			constexpr cmpId_type cId = T::id;
			//...
		}

		template<typename T>
		inline bool hasComponent(cmpId_type cId) {
			constexpr cmpId_type cId = T::id;
			//..
		}

		Entity();
		virtual ~Entity();
		inline void setContext(Manager* mngr); //...
		inline bool isAlive(); //...
		inline void setAlive(bool alive); //...
			//...
	private:
		bool alive_;
		Manager* mngr_;
		std::vector<Component*> currCmps_;
		std::array<Component*, ecs::maxComponentId> cmps_;
	};

}

