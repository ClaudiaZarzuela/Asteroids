#pragma once
#include "GameState.h"
#include "PauseState.h"
#include "MainMenuState.h"
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
	virtual void update();
	virtual string getStateID() const { return playID; }
	void checkCollision();
};

