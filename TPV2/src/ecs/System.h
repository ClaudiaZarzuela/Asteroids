#pragma once
#include "Manager.h"

class System {
public:
	System() {};
	virtual ~System() { }
	void setContext(Manager* mngr) {
		mngr_ = mngr;
	}
	virtual void initSystem() { }
	virtual void update() { }
	virtual void recieve(const ecs::Message& m) { }
protected:
	Manager* mngr_;
};


