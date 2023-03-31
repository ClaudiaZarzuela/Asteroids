#include "../checkML.h"
#include "Game.h"
#include <iostream>
#include <SDL.h>
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"

// inicializa SDL, las texturas, los textos y la maquina de estados
void Game::init() {

	SDLUtils::init("Asteroids!", 800, 600,
		"resources/resources/config/sdlutilsdemo.resources.json");
	/*auto& sdl = *SDLUtils::instance();
	renderer = sdl.renderer();*/
	
	//manager_ = Manager::instance();
	
	Manager::instance()->addSystem<FighterSystem>();
	Manager::instance()->addSystem<AsteroidsSystem>();
	Manager::instance()->addSystem<BulletSystem>();
	Manager::instance()->addSystem<CollisionsSystem>();
	Manager::instance()->addSystem<GameCtrlSystem>();
	Manager::instance()->addSystem<RenderSystem>();
	//Manager::instance()->addSystem<BulletSystem>(ecs::_sys_BULLETS);
}

//Destructora de la clase
Game::~Game() {
	//delete  gameStateMachine;
	/*for (int i = 0; i < NUM_TEXTURES; ++i) delete textures[i];
	for (int i = 0; i < NUM_TEXTS; ++i) delete texts[i];
	SDL_DestroyRenderer(renderer);*/
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// bucle principal del juego
void Game::run() {
	// Initialise the SDLGame singleton
	auto& sdl = *SDLUtils::instance();
	auto& ih = *InputHandler::instance();
	while (!exit_) {
		Uint32 startTime = sdl.currRealTime();
		// update the event handler
		ih.refresh();
		//gameStateMachine->currentState()->inputHandler();
		//gameStateMachine->currentState()->update();
		// clear screen
		//sdl.clearRenderer();
		Manager::instance()->update();
		//gameStateMachine->render();
		// present new frame
		//sdl.presentRenderer();
		Manager::instance()->flushMessages();
		Uint32 frameTime = sdl.currRealTime() - startTime;
		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
		Manager::instance()->refresh();
		if (InputHandler::instance()->closeWindowEvent())
			exit_ = true;
	}
}