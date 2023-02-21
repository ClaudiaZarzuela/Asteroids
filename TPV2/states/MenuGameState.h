#pragma once
#include "GameState.h"

// CLase MENUGAMESTATE que hereda de GAMESTATE
class MenuGameState : public GameState {
protected:
	Texture* background = nullptr;
	SDL_Rect rectBack;

	Vector2D posB;
	int widthB = 0;
	int heightB = 0;

	// Constructora de la clase
	MenuGameState(Game* game);

	// Metodo protegido de la clase
	void render() const;
};

