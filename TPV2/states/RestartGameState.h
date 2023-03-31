#pragma once
#include "../src/checkML.h"
#include "GameState.h"
#include "../src/game/Game.h"
#include <string>

class PlayState;
	
class RestartGameState: public GameState {
private:
	static const std::string restartID;
	PlayState* play_;
public:
	// Constructora de la clase
	RestartGameState(PlayState* play);
	// Metodos publicos de la clase
	void update() override;
	// Getters
	virtual std::string getStateID() const { return restartID; }
};


