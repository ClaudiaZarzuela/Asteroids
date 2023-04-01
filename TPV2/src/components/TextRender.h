#pragma once
#include "../checkML.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"

// componente encargado de renderizar texto en pantalla
struct TextRender: public Component
{
public:
	// id
	constexpr static ecs::cmpId_type id = ecs::_RENDERTEXT;
	// metodos publicos de la clase
	TextRender(Texture* t, int x_, int y_) : x(x_), y(y_), text(t) {};
	virtual ~TextRender() {};
	void render();
	Texture* getTexture() { return text; }
	void setTexture(Texture* t1) { text = t1; }
	Vector2D getPos() { return Vector2D(x, y); }

private:
	int x = 0;
	int y = 0;
	Texture* text;

};

