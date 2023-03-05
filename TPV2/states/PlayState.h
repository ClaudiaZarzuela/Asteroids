#pragma once
#include "../src/checkML.h"
#include "GameState.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "RestartGameState.h"
#include "../src/game/AsteroidManager.h"
#include "../src/game/CollisionsManager.h"

// Clase PLAYSTATE que hereda de GAMESTATE
class PlayState :public GameState
{
private:
	Entity* caza;
	AsteroidManager* aManager;
	CollisionsManager* cManager;
	static const string playID;

public:
	// Constructora de la clase
	PlayState();
	~PlayState() {
		delete aManager;
		aManager = nullptr;
		delete cManager;
		cManager = nullptr;
	}
	virtual void update();
	void inputHandler() override;
	void changeState();
	Manager* getManager() { return manager_; }
	AsteroidManager* getAManager() { return aManager; }
	virtual string getStateID() const { return playID; }
};

