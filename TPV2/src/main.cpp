// This file is part of the course TPV2@UCM - Samir Genaim
#include "checkML.h"
#include <iostream>
#include "sdlutils/sdlutils_demo.h"
#include "game/Game.h"

// main
int main(int ac, char **av) {
	// para comprobar si hay memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try {	
		Game::instance()->init();
		Game::instance()->run();
		//delete(game);
	} catch (const std::string &e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	} catch (const char *e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	} catch (const std::exception &e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	} catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}

	return 0;
}

