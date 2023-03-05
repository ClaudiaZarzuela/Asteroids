#pragma once
#include "../src/checkML.h"
#include <deque>
#include <list>

using namespace std;

class GameState;
// Clase GAMESTATEMACHINE
class GameStateMachine
{
private:
	deque<GameState*> gameStateStack;

public:

	// Constructora y destructora de la clase
	GameStateMachine() {};
	virtual ~GameStateMachine();

	// Metodos publicos de la clase
	GameState* currentState() {
		if (!gameStateStack.empty()) return gameStateStack.front();
		else return nullptr;
	}
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();
	void emptyStates();
	void render();
	void refresh();

	GameState* lastState() {
		if (!gameStateStack.empty()) return gameStateStack.back();
		else return nullptr;
	}

};


