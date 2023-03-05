#pragma once
#include "../checkML.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"

// componente encargado de mantener y mostar en pantalla la salud de la nave
class Health :public Component
{
public:
	// id
	constexpr static ecs::cmpId_type id = ecs::_HEALTH;
	// metodos publicos de la clase
	Health(Texture* tex, int h) :
		tex_(tex), maxLives(h) {
		actLives = maxLives;
	}
	virtual ~Health();
	void render() override;
	void resetLives() { actLives = maxLives; }
	int getLives() { return actLives; }
	void loseLife() { actLives--; }
private:
	Texture* tex_;
	int textSize = 30;
	int maxLives = 3;
	int actLives;
};

