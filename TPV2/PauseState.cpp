#include "PauseState.h"

// Identificador de clase de estado
const string PauseState::pauseID = "PAUSE";

// Constructora de la clase, que difine sus botones y fondo
PauseState::PauseState(Game* game) : MenuGameState(game) {
	gameObjects.push_back(new MenuButton(game, Vector2D(WIN_WIDTH / 2 - 90, WIN_HEIGHT / 2 - 110), 100, 150, game->getTexture(Resume), resumeGame));
	gameObjects.push_back(new MenuButton(game, Vector2D(WIN_WIDTH / 2 - 90, WIN_HEIGHT / 2), 100, 150, game->getTexture(Save), saveGame));
	gameObjects.push_back(new MenuButton(game, Vector2D(WIN_WIDTH / 2 - 90, WIN_HEIGHT / 2 + 110), 100, 150, game->getTexture(Main), goToMainMenu));
	background = game->getTexture(Pause);
}

// Metodo (callback) que reanuda el juego
void PauseState::resumeGame(Game* game) {
	game->gameStateMachine->currentState()->deleteState();
	game->gameStateMachine->popState();
}

// Metodo (callback) que guarda la informacion de la partida y pide al usuario un codigo que le permita recuperarla
void PauseState::saveGame(Game* game) {
	ShowWindow(GetConsoleWindow(), SW_NORMAL); // Muestra la consola para que el usuario introduzca el codigo
	string code;
	cout << "Introduce el codigo de guardado: ";
	cin >> code;
	ShowWindow(GetConsoleWindow(), SW_MINIMIZE); // Esconde la consola para que no estorbe al comenzar el juego
	game->gameStateMachine->popState();
	PlayState* play = static_cast<PlayState*>(game->gameStateMachine->currentState());
	play->saveToFile(code);
}

// Metodo (callback) para volver al MainMenu
void PauseState::goToMainMenu(Game* game) {
	game->gameStateMachine->currentState()->deleteState();
	game->gameStateMachine->changeState(new MainMenuState(game));
}