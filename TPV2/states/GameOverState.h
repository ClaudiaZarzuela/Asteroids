#pragma once
#include "GameState.h"
#include "MainMenuState.h"
class GameOverState: public GameState 
{
private:
	static const string gameOverID;
	bool exit_ = false;
	int x, y;
	string infoState;

public:
	// Constructora de la clase
	GameOverState(string stateInfo);
	// Metodos publicos de la clase
	void inputHandler() override;
	// Getters
	virtual string getStateID() const { return gameOverID; }
};