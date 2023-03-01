#pragma once
#include "GameState.h"
#include "PauseState.h"
#include "MainMenuState.h"

// Clase PLAYSTATE que hereda de GAMESTATE
class PlayState :public GameState
{
private:
	Entity* caza;
	Entity* asteroids;
	static const string playID;

public:

	// Constructora de la clase
	PlayState();
	virtual string getStateID() const { return playID; }
};

