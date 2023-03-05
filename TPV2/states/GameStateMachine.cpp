#include "../src/checkML.h"
#include "GameStateMachine.h"
#include "GameState.h"

// Destructora de la clase
GameStateMachine:: ~GameStateMachine() {
	while (!gameStateStack.empty()) {
		delete gameStateStack.front();
		gameStateStack.pop_front();
	}

}

// Añade un estado a lo alto de la pila
void GameStateMachine::pushState(GameState* pState) {
	gameStateStack.push_front(pState);
}

// Elimina el primer estado de la pila
void GameStateMachine::popState() {
	if (!gameStateStack.empty()) {
		delete gameStateStack.front();
		gameStateStack.pop_front();
	}
}

// Elimina el primer estado de la pila y añade uno nuevo
void GameStateMachine::changeState(GameState* pState) {

	if (!gameStateStack.empty()) {
		if (gameStateStack.front()->getStateID() == pState->getStateID()) return;
		delete gameStateStack.front();
		gameStateStack.pop_front();
	}
	gameStateStack.push_front(pState);
}

void GameStateMachine::emptyStates() {
	while (!gameStateStack.empty()) {
		delete gameStateStack.front();
		gameStateStack.pop_front();
	}
}
