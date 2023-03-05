#pragma once
#include "../src/checkML.h"
#include "GameState.h"
#include "../src/game/Game.h"

class PlayState;
class RestartGameState: public GameState
{
private:
	static const string restartID;
	PlayState* play_;
public:
	// Constructora de la clase
	RestartGameState(PlayState* play);
	// Metodos publicos de la clase
	void inputHandler() override;
	// Getters
	virtual string getStateID() const { return restartID; }
};


