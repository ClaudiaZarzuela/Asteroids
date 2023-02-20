#pragma once
#include "MenuGameState.h"
#include "PlayState.h"
#include "EndState.h"
#include "MainMenuState.h"
#include "Game.h"
#include "checkML.h"

// Clase PAUSESTATE que hereda de MENUGAMESTATE
class PauseState : public MenuGameState {
private:
	static const string pauseID;

public:
	// Constructora de la clase
	PauseState(Game* game);

	// Metodos publicos de la clase
	static void resumeGame(Game* game);
	static void saveGame(Game* game);
	static void goToMainMenu(Game* game);

	// Getters
	virtual string getStateID() const { return pauseID; }
};

