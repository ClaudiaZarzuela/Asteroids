#pragma once
#include "../checkML.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "../sdlutils/SDLUtils.h"

// componente encargado de renderizar texto en pantalla
struct TextRender: public Component
{
public:
	// id
	constexpr static ecs::cmpId_type id = ecs::_RENDERTEXT;
	// metodos publicos de la clase
	TextRender(Texture* t, int x_, int y_) : x(x_), y(y_), text1(t), text2(nullptr) {};
	TextRender(Texture* t1, Texture* t2, int x_, int y_) : x(x_), y(y_), text1(t1), text2(t2) {};
	virtual ~TextRender() {};

private:
	int x = 0;
	int y = 0;
	Texture* text1;
	Texture* text2;
};

