#pragma once
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "../sdlutils/SDLUtils.h"

class TextRender: public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_RENDERTEXT;
	TextRender(Texture* t, int x_, int y_) : x(x_), y(y_), text1(t), text2(nullptr) {};
	TextRender(Texture* t1, Texture* t2, int x_, int y_) : x(x_), y(y_), text1(t1), text2(t2) {};
	virtual ~TextRender() {};
	void render() override;
private:
	int x = 0;
	int y = 0;
	Texture* text1;
	Texture* text2;

};

