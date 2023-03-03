#pragma once

class Entity;
class Manager;
	
class Component {
public:
	Component() : ent_(), mngr_() {}
	virtual ~Component() { }
	inline void setContext(Entity* ent, Manager* mngr) { 
		ent_ = ent;
		mngr_ = mngr;
	}
		
	virtual void initComponent() { }
	virtual void update() { }
	virtual void render() { }
protected:
	Entity* ent_;
	Manager* mngr_;
};

