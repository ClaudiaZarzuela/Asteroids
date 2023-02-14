#pragma once
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

class Game
{
private:
	Manager* manager_;
	bool exit_ = false;
	//noseque singleton
public:
	void init();
	void run();
};

