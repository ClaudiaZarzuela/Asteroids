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
	MainMenuState(Game* game);

	// Metodos publicos de la clase
	static void startGame(Game* g);
	static void loadGame(Game* g);
	static void exitGame(Game* g);
	virtual string getStateID() const { return menuID; }
};

