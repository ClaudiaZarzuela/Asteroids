#pragma once
#include "../checkML.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "../sdlutils/SDLUtils.h"

// componente encargado de renderizar texto en pantalla
class TextRender: public Component
{
public:
	// id
	constexpr static ecs::cmpId_type id = ecs::_RENDERTEXT;
	// metodos publicos de la clase
	TextRender(Texture* t, int x_, int y_) : x(x_), y(y_), text(t) {};
	virtual ~TextRender() {};
	void render() override;
private:
	int x = 0;
	int y = 0;
	Texture* text;

};

