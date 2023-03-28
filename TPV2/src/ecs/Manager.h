#pragma once
#include "../checkML.h"
#include "../game/ecs_def.h"
#include <vector>
#include <array>
#include "Entity.h"
#include "System.h"

// declaracion de la clase padre manager
class Manager {
public:
	Manager();
	virtual ~Manager();
	inline Entity* addEntity(ecs::grpId_type gId);
	inline const auto& getEntitiesByGroup(ecs::grpId_type gId);
	inline void setHandler(ecs::hdlrId_type hId, Entity* e);
	inline Entity* getHandler(ecs::hdlrId_type hId);
	void update();
	void render();
	void refresh();
	//new methods in next slides
	template<typename T, typename ...Ts>
	inline T* addComponent(Entity* e, Ts&& ...args) {
		T* c = new T(std::forward<Ts>(args)...);
		constexpr cmpId_type cId = T::id;
		removeComponent<T>()
			e->currCmps_.push_back(c);
		e->cmps_[cId] = c;
		e->setContext(e, this);
		e->initComponent();
		return c;
	}
	template<typename T>
	inline void removeComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		if (e->cmps_[cId] != nullptr) {
			auto iter = std::find(e->currCmps_.begin(),
				e->currCmps_.end(),
				e->cmps_[cId]);
			e->currCmps_.erase(iter);
			delete e->cmps_[cId];
			e->cmps_[cId] = nullptr;
		}
	}
	template<typename T>
	inline bool hasComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		return e->cmps_[cId] != nullptr;
	}
	template<typename T>
	inline T* getComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		return static_cast<T*>(e->cmps_[cId]);
	}
	inline void setAlive(Entity* e, bool alive) {
		e->alive_ = alive;
	}
	inline bool isAlive(Entity* e) {
		return e->alive_;
	}
	inline ecs::grpId_type groupId(Entity* e) {
		return e->gId_;
	}

	template<typename T, typename ...Ts>
	inline T* addSystem(Ts &&... args) {
		constexpr sysId_type sId = T::id;
		removeSystem<T>();
		System* s = new T(std::forward<Ts>(args)...);
		s->setContext(this);
		s->initSystem();
		sys_[sId] = s;
		return static_cast<T*>(s);
	}
	template<typename T>
	inline T* getSystem() {
		constexpr sysId_type sId = T::id;
		return static_cast<T*>(sys_[sId]);
	}
	template<typename T>
	inline void removeSystem() {
		constexpr sysId_type sId = T::id;
		if (sys_[sId] != nullptr) {
			delete sys_[sId];
			sys_[sId] = nullptr;
		}
	}
	inline void send(const ecs::Message& m, bool delay = false) {
		if (!delay) {
			for (System* s : sys_) {
				if (s != nullptr)
					s->recieve(m);
			}
		}
		else {
			msgs_.emplace_back(m);
		}
	}
	inline void flushMessages() {
		std::swap(msgs_, aux_msgs_);
		for (auto& m : aux_msgs_) {
			for (System* s : sys_) {
				if (s != nullptr)
					s->recieve(m);
			}
		}
		aux_msgs_.clear();
	}

private:
	std::vector<ecs::Message> msgs_;
	std::vector<ecs::Message> aux_msgs_;
	std::array<System*, ecs::maxSysId> sys_;
	std::array<Entity*, ecs::maxHdlrId> hdlrs_;
	std::array<std::vector<Entity*>, ecs::maxGroupId> entsByGroup_;
};



//class Manager {
//private:
//	std::array<std::vector<Entity*>, ecs::maxGroupId> ents_;
//	std::array<Entity*, ecs::maxHdlrId> hdlrs_;
//
//public:
//	// metodos publicos de la clase, heredados por el resto de managers
//	Manager(): ents_(), hdlrs_() {
//		for (auto& groupEntities : ents_) {
//			groupEntities.reserve(100);
//		}
//	};
//
//	virtual ~Manager(){
//		for (auto& ents : ents_) {
//			for (auto e : ents) {
//				delete[] e;
//				e = nullptr;
//			}
//		}
//	};
//
//	inline void setHandler(ecs::hdlrId_type hId, Entity* e) {
//		hdlrs_[hId] = e;
//	}
//
//	inline Entity* getHandler(ecs::hdlrId_type hId) {
//		return hdlrs_[hId];
//	}
//	Entity* addEntity(ecs::grpId_type gId = ecs:: _grp_GENERAL);
//	void refresh();
//	void update();
//	void render();
//	void inputHandler();
//	inline const auto& getEntities(ecs::grpId_type gId) { return ents_[gId]; }
//	
//};

