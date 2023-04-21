#pragma once
#include "../checkML.h"
#include "../game/ecs_def.h"

class Entity;
class Manager;
// declaracion de la clase padre component
struct Component {
	Component() : ent_(), mngr_() { }
	virtual ~Component() { }
	inline void setContext(Entity* ent, Manager* mngr) {
		ent_ = ent;
		mngr_ = mngr;
	}
	virtual void initComponent() { }
protected:
	Entity* ent_;
	Manager* mngr_;
};
