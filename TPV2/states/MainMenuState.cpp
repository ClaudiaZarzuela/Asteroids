#include "MainMenuState.h"

// Identificador de clase de estado
const string MainMenuState::menuID = "MENU";

// Constructora de la clase, que difine sus botones y fondo
MainMenuState::MainMenuState() :GameState() {
	/*gameObjects.push_back(new MenuButton(game, Vector2D(WIN_WIDTH / 2 - 90, WIN_HEIGHT / 2 - 110), 100, 150, game->getTexture(Start), startGame));
	gameObjects.push_back(new MenuButton(game, Vector2D(WIN_WIDTH / 2 - 90, WIN_HEIGHT / 2), 100, 150, game->getTexture(Load), loadGame));
	gameObjects.push_back(new MenuButton(game, Vector2D(WIN_WIDTH / 2 - 90, WIN_HEIGHT / 2 + 110), 100, 150, game->getTexture(Exit), exitGame));
	background = game->getTexture(Title);*/
}
void MainMenuState::changeState() {
	Game::instance()->gameStateMachine->currentState()->deleteState();
	Game::instance()->gameStateMachine->changeState(new PlayState());
}
//
//// Metodo (callback) para empezar el juego
//void MainMenuState::startGame(Game* g) {
//	g->gameStateMachine->currentState()->deleteState();
//	g->gameStateMachine->changeState(new PlayState(g, " "));
//};
//
//// Metodo (callback) para cargar una partida
//void MainMenuState::loadGame(Game* g) {
//	ShowWindow(GetConsoleWindow(), SW_NORMAL); // Muestra la consola para que el usuario introduzca el codigo
//	string file;
//	cout << "Introduce code of your last game: ";
//	cin >> file;
//	ShowWindow(GetConsoleWindow(), SW_MINIMIZE); // Esconde la consola para que no estorbe al comenzar el juego
//	try {
//		g->gameStateMachine->currentState()->deleteState();
//		g->gameStateMachine->changeState(new PlayState(g, file));
//	}
//	catch (FileFormatError e) {
//		cout << e.what() << endl;
//	}
//	catch (FileNotFoundError e) { // Si el usuario introduce un codigo que no esta guardado, se le crea una partida nueva
//		cout << e.what() << endl;
//		cout << "We couldn't find a save file with that name so we will start a new game for you";
//		g->gameStateMachine->currentState()->deleteState();
//		g->gameStateMachine->changeState(new PlayState(g, " "));
//	}
//
//}
//
//// Metodo (callback) para salir de la aplicacion
//void MainMenuState::exitGame(Game* g) {
//	g->exitGame();
//}