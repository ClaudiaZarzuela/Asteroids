#pragma once
#include "../game/ecs_def.h"
#include "Component.h"
#include<vector>
#include<array>
#include<utility>
using namespace std;
class Manager;
class Entity {
public:
	Entity();
	template<typename T>
	inline void removeComponent() {
		constexpr ecs::cmpId_type cId = T::id;
		if (cmps_[cId] != nullptr) {
			auto iter = std::find(currCmps_.begin(),
				currCmps_.end(),
				cmps_[cId]);
			currCmps_.erase(iter);
			delete cmps_[cId];
			cmps_[cId] = nullptr;
		}
	}

	template<typename T>
	inline T* getComponent() {
		constexpr ecs::cmpId_type cId = T::id;
		return static_cast<T*>(cmps_[cId]);
	}

	template<typename T>
	inline bool hasComponent() {
		constexpr ecs::cmpId_type cId = T::id;
		return cmps_[cId] != nullptr;
	}

	template<typename T, typename ...Ts>
	inline T* addComponent(Ts&& ...args) {
		T* c = new T(std::forward<Ts>(args)...);
		constexpr ecs::cmpId_type cId = T::id;
		removeComponent<T>();
		currCmps_.push_back(c);
		cmps_[cId] = c;
		c->setContext(this, mngr_);
		c->initComponent();
		return c;
	};
	virtual ~Entity() {
		for (auto c : currCmps_) {
			delete c;
		}
	};
	inline bool isAlive() { return alive_; };
	inline void setAlive(bool alive) {
		alive_ = alive;
	};

	inline void update() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->update();
	}
	inline void render() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->render();
	}
private:
	bool alive_;
	Manager* mngr_;
	vector<Component*> currCmps_;
	array<Component*, ecs::maxComponentId> cmps_;
};



