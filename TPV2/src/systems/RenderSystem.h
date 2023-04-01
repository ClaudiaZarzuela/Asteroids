#pragma once
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include <SDL_image.h>
#include <string>
#include <list>


const int NUM_TEXTURES = 5;
const int NUM_TEXTS = 4;
	struct Textures
	{
		std::string filename;
		int rows;
		int cols;
	};
	// Estructura que contiene variables para el contenido del texto y su color de las letras y del background
	struct Texts
	{
		std::string content;
		int textColor;
		int backgroundColor;
	};
// enmunerados para los distintos estados, texturas y textos del juego
static const enum TextureNames {
	NAVE = 0, ASTEROID = 1, HEALTH = 2, BULLET = 3, ASTEROID_GOLD = 4
};
static const enum TextNames {
	MAINMENU = 0, PAUSA = 1, LOSE = 2, WIN = 3
};
class RenderSystem : public System {
public:

	// Estructura que contiene variables para el nombre de las imagenes de la textura y su numero de filas y columnas

	constexpr static ecs::sysId_type id = ecs::_sys_RENDER;
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void recieve(const ecs::Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
	// - Dibujar las vidas (siempre).
	// - Dibujar los mensajes correspondientes: si el juego está parado, etc (como en
	// la práctica 1)
	void update() override;

private:
	Textures texture[NUM_TEXTURES] = {
		{ " ../../resources/resources/images/fighter.png", 1, 1 },
		{ " ../../resources/resources/images/asteroid.png", 5, 6 },
		{ " ../../resources/resources/images/heart.png", 1, 1 },
		{ " ../../resources/resources/images/fire.png", 1, 1 },
		{ " ../../resources/resources/images/asteroid_gold.png", 5, 6 }
	};
	Texts text[NUM_TEXTS] = {
		{ "Press space to Start", 0x112233ff,0},
		{ "Press space to Continue", 0x112233ff, 1 },
		{ "Game Over: Loser!", 0x112233ff, 0 },
		{ "Game Over: You Win!", 0x112233ff, 0 }
	};

	~RenderSystem();
	Texture* textures[NUM_TEXTURES];
	Texture* texts[NUM_TEXTS];
	SDL_Renderer* renderer = nullptr;
	Entity* fighter = nullptr;
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_. 
	void onRoundStart();
	void onRoundOver();
	void onGameStart();
	void onGameOver();
	void inGameObjects();
	void animateAsteroids();
	void changeText();
	Entity* text1_ = nullptr;
	Entity* text2_ = nullptr;
	Uint8 winner_; // 0 - None, 1 - Asteroid, 2- Fighter
	Uint8 state_; // El estado actual de juego (como en GameCtrlSystem)
	int frameTime = 0;
};