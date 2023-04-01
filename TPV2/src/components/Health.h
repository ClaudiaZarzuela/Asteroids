#pragma once
#include "../checkML.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"

// componente encargado de mantener la salud de la nave
struct Health :public Component
{
public:
	// id
	constexpr static ecs::cmpId_type id = ecs::_HEALTH;
	// metodos publicos de la clase
	Health(int h) :
	    maxLives(h) {
		actLives = maxLives;
	}
	virtual ~Health();;
	void resetLives() { actLives = maxLives; }
	int getLives() { return actLives; }
	void loseLife() { actLives--; }

private:
	int textSize = 30;
	int maxLives = 3;
	int actLives;
};

