#pragma once
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include <SDL_image.h>
#include <string>
#include <list>
#include "../../states/GameStateMachine.h"
#include "../../states/PlayState.h"
#include "../utils/Singleton.h"
#include "../sdlutils/SoundEffect.h"
#include "../sdlutils/Music.h"

using namespace std;

const int NUM_TEXTURES = 5;

enum GameStates {
	PLAY = 0,
	PAUSE = 1,
	END = 2,
	MENU = 3
};

static const enum TextureNames {
	NAVE = 0, ASTEROID = 1, HEALTH=2, BULLET =3, ASTEROID_GOLD = 4
};
// Estructura que contiene variables para el nombre de las imagenes de la textura y su numero de filas y columnas
struct Textures
{
	string filename;
	int rows;
	int cols;
};

class Game : public Singleton<Game>
{
	friend Singleton<Game>;
private:

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit_ = false;
	Textures texture[NUM_TEXTURES] = {
		{ " ../../resources/resources/images/fighter.png", 1, 1 },
		{ " ../../resources/resources/images/asteroid.png", 5, 6 },
		{ " ../../resources/resources/images/heart.png", 1, 1 },
		{ " ../../resources/resources/images/fire.png", 1, 1 },
		{ " ../../resources/resources/images/asteroid_gold.png", 5, 6 }
	};
	Texture* textures[NUM_TEXTURES];
	Game() {};

    
public:
	virtual ~Game();
	//Constructuctora y destructora de Game

	// Estado actual del juego
	GameStateMachine* gameStateMachine = nullptr;
	void init();
	void run();

	// Getters
	Texture* getTexture(int tx) { return textures[tx]; }
	GameStateMachine* getStateMachine() { return gameStateMachine; }
};

