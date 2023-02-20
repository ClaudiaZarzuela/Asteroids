#pragma once
#include <list>
#include <windows.h>
#include "../TPV2/src/ecs/Entity.h"
#include "../TPV2/src/sdlutils/Texture.h"
#include "../TPV2/src/utils/Vector2D.h"

using namespace std;

class Game;
// Clase GAMESTATE
class GameState
{
protected:
	// Constructora protegida
	GameState(Game* g) : game(g) {};
	list<Entity*> gameObjects;
	Game* game;
	bool deleted = false;

public:

	// Destructora de la clase
	virtual ~GameState();

	// Metodos publicos de la clase
	void deleteState() { deleted = true; };
	virtual void update();
	virtual void render() const;
	virtual void handleEvent(SDL_Event event);

	// Getters
	virtual string getStateID() const = 0;
};

