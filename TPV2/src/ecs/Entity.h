#pragma once
#include "../game/ecs_def.h"
#include "Component.h"
#include<vector>
#include<array>

using namespace std;

class Manager;
class Entity {
public:
	template<typename T>
	inline void removeComponent(ecs::cmpId_type cId) {
		constexpr ecs::cmpId_type cId = T::id;
		//...
	}

	template<typename T>
	inline T* getComponent(ecs::cmpId_type cId) {
		constexpr ecs::cmpId_type cId = T::id;
		//...
	}

	template<typename T>
	inline bool hasComponent(ecs::cmpId_type cId) {
		constexpr ecs::cmpId_type cId = T::id;
		//...
	}

	template<typename T, typename ...Ts>
	inline T* addComponent(ecs::cmpId_type cId, Ts&& ...args) {
		T* c = new T(std::forward<Ts>(args)...);
		removeComponent(cId);
			currCmps_.push_back(c);
		cmps_[cId] = c;
		c->setContext(this, mngr_);
		c->initComponent();
		return c;
	}
	Entity(): mngr_(nullptr), cmps_(), currCmps_(), alive_() {
		currCmps_.reserve(ecs::maxComponentId);
	};
	virtual ~Entity() {
		for (auto c : currCmps_) {
			delete c;
		}
	};
	inline void setContext(Manager* mngr) {
		mngr_ = mngr;
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



