#pragma once
#include "../checkML.h"
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include <SDL_image.h>
#include <string>
#include <list>


const int NUM_TEXTURES = 9;
const int NUM_TEXTS = 4;
// Estructura que contiene variables para el nombre de las imagenes de la textura y su numero de filas y columnas
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
	constexpr static ecs::sysId_type id = ecs::_sys_RENDER;
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void recieve(const ecs::Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// - Dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
	// - Dibujar las vidas (siempre).
	// - Dibujar los mensajes correspondientes: si el juego est� parado, etc (como en
	// la pr�ctica 1)
	void update() override;

private:
	Textures texture[NUM_TEXTURES] = {
		{ " ../../resources/resources/images/fighter.png", 1, 1 },
		{ " ../../resources/resources/images/asteroid.png", 5, 6 },
		{ " ../../resources/resources/images/heart.png", 1, 1 },
		{ " ../../resources/resources/images/fire.png", 1, 1 },
		{ " ../../resources/resources/images/asteroid_gold.png", 5, 6 },
		{ " ../../resources/resources/images/singleplayer.png", 1, 1 },
		{ " ../../resources/resources/images/multiplayer.png", 1, 1 },
		{ " ../../resources/resources/images/client.png", 1, 1 },
		{ " ../../resources/resources/images/host.png", 1, 1 }
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
	// metodo que renderiza los grupos exclusivos del playstate (asteroides y balas)
	void inGameObjects();
	// metodo que anima los asteroides
	void animateAsteroids();
	// metodo que cambia el texto que se muestra en pantalla en cada estado
	void changeText();
	Entity* text1_ = nullptr;
	Entity* text2_ = nullptr;
	Uint8 state_; // El estado actual de juego (como en GameCtrlSystem)
	int frameTime = 0;
};