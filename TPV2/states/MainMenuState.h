#pragma once
#include "../src/checkML.h"
#include "PauseState.h"
#include "PlayState.h"
#include "GameState.h"
#include "../src/game/Game.h"


// Clase MAINMENUSTATE que hereda de MENUGAMESTATE
class MainMenuState : public GameState
{
private:
	static const string menuID;
public:

	// Constructora de la clase
	MainMenuState();

	// Metodos publicos de la clase
	void inputHandler() override;
	virtual string getStateID() const { return menuID; }
};

