#pragma once
#include "../src/checkML.h"
#include "GameState.h"
#include "MainMenuState.h"
class PlayState;
class GameOverState: public GameState 
{
private:
	static const string gameOverID;
	string infoState;
	PlayState* play_;
public:
	// Constructora de la clase
	GameOverState(string stateInfo, PlayState* play);
	void update() override;
	// Getters
	virtual string getStateID() const { return gameOverID; }
};
