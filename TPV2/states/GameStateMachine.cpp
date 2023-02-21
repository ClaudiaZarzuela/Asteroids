#include "GameStateMachine.h"
#include "GameState.h"

// Destructora de la clase
GameStateMachine:: ~GameStateMachine() {
	while (!gameStateStack.empty()) {
		delete gameStateStack.top();
		gameStateStack.pop();
	}

}

// Añade un estado a lo alto de la pila
void GameStateMachine::pushState(GameState* pState) {
	gameStateStack.push(pState);
}

// Elimina el primer estado de la pila
void GameStateMachine::popState() {
	if (!gameStateStack.empty()) {
		delete gameStateStack.top();
		gameStateStack.pop();
	}
}

// Elimina el primer estado de la pila y añade uno nuevo
void GameStateMachine::changeState(GameState* pState) {

	if (!gameStateStack.empty()) {
		if (gameStateStack.top()->getStateID() == pState->getStateID()) return;
		delete gameStateStack.top();
		gameStateStack.pop();
	}
	gameStateStack.push(pState);
}

