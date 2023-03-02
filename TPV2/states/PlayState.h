#pragma once
#include "GameState.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "../src/game/AsteroidManager.h"
// Clase PLAYSTATE que hereda de GAMESTATE
class PlayState :public GameState
{
private:
	Entity* caza;
	Entity* bullet;
	AsteroidManager* amanager;
	static const string playID;

public:

	// Constructora de la clase
	PlayState();
	virtual string getStateID() const { return playID; }
};

