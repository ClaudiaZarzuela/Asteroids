#pragma once
#include "MenuGameState.h"
#include "PauseState.h"
#include "PlayState.h"
#include "../src/game/Game.h"


// Clase MAINMENUSTATE que hereda de MENUGAMESTATE
class MainMenuState : public MenuGameState
{
private:
	static const string menuID;
public:

	// Constructora de la clase
	MainMenuState();

	// Metodos publicos de la clase
	static void startGame();
	static void loadGame();
	static void exitGame();
	virtual string getStateID() const { return menuID; }
};

