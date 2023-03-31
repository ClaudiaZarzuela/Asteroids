#pragma once
#include "../game/ecs_def.h"

class Manager;
class System {
public:
	System() {};
	virtual ~System() { }
	void setContext(Manager* mngr) {
		mngr_ = mngr;
	}
	virtual void initSystem(){};
	virtual void update() {}
	virtual void recieve(const ecs::Message& m) { }
protected:
	Manager* mngr_ = nullptr;
	enum states{MAINMENU, PLAY, RESTART, PAUSE, GAMEOVER};
	int currentState = MAINMENU;
};


