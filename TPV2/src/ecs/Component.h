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
	/*virtual void update() { }
	virtual void render() { }*/
protected:
	Entity* ent_;
	Manager* mngr_;
};

//class Component {
//public:
//	// metodos publicos de la case, hererdados por el resto de componentes
//	Component() : ent_(), mngr_() {}
//	virtual ~Component() { }
//	inline void setContext(Entity* ent, Manager* mngr) { 
//		ent_ = ent;
//		mngr_ = mngr;
//	}
//		
//	virtual void initComponent() { }
//	virtual void update() { }
//	virtual void render() { }
//	virtual void handleInput(){}
//protected:
//	Entity* ent_;
//	Manager* mngr_;
//};

