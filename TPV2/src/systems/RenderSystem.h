#pragma once
#include "../checkML.h"
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include <SDL_image.h>
#include <string>
#include <list>
#include "OnlineSystem.h"

const int NUM_TEXTURES = 9;
const int NUM_TEXTS = 5;
const int NUM_PLAYERS = 4;
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
	NAVE = 0, ASTEROID = 1, HEALTH = 2, BULLET = 3, ASTEROID_GOLD = 4, SINGLEPLAYER = 5, MULTIPLAYER = 6, CLIENT = 7, HOST = 8
};
static const enum TextNames {
	MAINMENU = 0, PAUSA = 1, LOSE = 2, WIN = 3, WAIT = 4
};
static const enum IDPlayers{
	P1 = 0, P2 = 1, P1_WON = 2, P2_WON = 3
};
class RenderSystem : public System {
public:
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
		{ "Game Over: You Win!", 0x112233ff, 0 },
		{ "Waiting for other player...", 0x112233ff, 0 }
	};

	~RenderSystem();
	Texture* textures[NUM_TEXTURES];
	Texture* texts[NUM_TEXTS];
	Texture* ids[NUM_PLAYERS];
	SDL_Renderer* renderer = nullptr;
	Entity* fighter = nullptr;
	// metodo que renderiza los grupos exclusivos del playstate (asteroides y balas)
	void asteroids();
	void bullets();
	// metodo que anima los asteroides
	void animateAsteroids();
	// metodo que cambia el texto que se muestra en pantalla en cada estado
	void changeText();
	void player();
	void playersOnline();
	void menuButtons();
	void waitingtext();
	void menuTexts();
	void bulletsOnline();
	void showWinner();
	void createNames(std::string p1, std::string p2);
	Entity* text1_ = nullptr;
	Entity* text2_ = nullptr;
	Entity* ID1_ = nullptr;
	Entity* ID2_ = nullptr;
	Uint8 state_ = GAMEMODE; // El estado actual de juego (como en GameCtrlSystem)
	int frameTime = 0;
	int winner;
};