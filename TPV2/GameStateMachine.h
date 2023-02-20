#pragma once
#include <stack>
#include <list>

using namespace std;

class GameState;
// Clase GAMESTATEMACHINE
class GameStateMachine
{
private:
	stack<GameState*> gameStateStack;

public:

	// Constructora y destructora de la clase
	GameStateMachine() {};
	virtual ~GameStateMachine();

	// Metodos publicos de la clase
	GameState* currentState() {
		if (!gameStateStack.empty()) return gameStateStack.top();
		else return nullptr;
	}
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

};


