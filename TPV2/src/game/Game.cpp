#include "Game.h"
#include <iostream>
#include <SDL.h>
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"

void Game::init() {

	SDLUtils::init("Asteroids!", 800, 600,
		"resources/resources/config/sdlutilsdemo.resources.json");
	auto& sdl = *SDLUtils::instance();
	renderer = sdl.renderer();
	for (int i = 0; i < NUM_TEXTURES; ++i)
	{
		textures[i] = new Texture(renderer, texture[i].filename, texture[i].rows, texture[i].cols);
	}
	for (int i = 0; i < NUM_TEXTS; ++i)
	{
		if (text[i].backgroundColor == 0) {
			texts[i] = new Texture(renderer, text[i].content, sdl.fonts().at("ARIAL24"), build_sdlcolor(text[i].textColor));

		}
		else texts[i] = new Texture(renderer, text[i].content, sdl.fonts().at("ARIAL24"), build_sdlcolor(text[i].textColor), build_sdlcolor(text[i].backgroundColor));
	}
	gameStateMachine = new GameStateMachine();
	gameStateMachine->pushState(new MainMenuState());
	//sdl.musics().at("imperial_march").play();
}

//Destructora de la clase
Game::~Game() {
	delete  gameStateMachine;
	for (int i = 0; i < NUM_TEXTURES; ++i) delete textures[i];
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void Game::run() {
	// Initialise the SDLGame singleton
	auto& sdl = *SDLUtils::instance();
	auto& ih = *InputHandler::instance();
	while (!exit_) {
		Uint32 startTime = sdl.currRealTime();
		// update the event handler
		ih.refresh();
		gameStateMachine->currentState()->inputHandler();
		gameStateMachine->currentState()->update();
		// clear screen
		sdl.clearRenderer();
		gameStateMachine->currentState()->render();
		// present new frame
		sdl.presentRenderer();
		Uint32 frameTime = sdl.currRealTime() - startTime;
		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
		gameStateMachine->currentState()->refresh();
	}
}