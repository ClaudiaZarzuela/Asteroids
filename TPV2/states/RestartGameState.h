#pragma once
#include "../src/checkML.h"
#include "GameState.h"
#include "../src/game/Game.h"

class RestartGameState: public GameState
{
private:
	static const string restartID;

public:
	// Constructora de la clase
	RestartGameState();
	// Metodos publicos de la clase
	void inputHandler() override;
	// Getters
	virtual string getStateID() const { return restartID; }
};


