#pragma once
#include "../checkML.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "../sdlutils/SDLUtils.h"

class TextRender: public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_RENDERTEXT;
	TextRender(Texture* t, int x_, int y_) : x(x_), y(y_), text(t) {};
	virtual ~TextRender() {};
	void render() override;
private:
	int x = 0;
	int y = 0;
	Texture* text;

};

