#pragma once
#include "MenuGameState.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "../src/game/Game.h"

// Clase PAUSESTATE que hereda de MENUGAMESTATE
class PauseState : public MenuGameState {
private:
	static const string pauseID;

public:
	// Constructora de la clase
	PauseState();

	// Metodos publicos de la clase
	static void resumeGame();
	static void saveGame();
	static void goToMainMenu();

	// Getters
	virtual string getStateID() const { return pauseID; }
};

