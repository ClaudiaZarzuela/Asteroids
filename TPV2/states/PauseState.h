#pragma once
#include "../src/checkML.h"
#include "GameState.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "../src/game/Game.h"

// Clase PAUSESTATE que hereda de MENUGAMESTATE
class PauseState : public GameState {
private:
	static const string pauseID;

public:
	// Constructora de la clase
	PauseState();
	// Metodos publicos de la clase
	void inputHandler() override;

	// Getters
	virtual string getStateID() const { return pauseID; }
};

