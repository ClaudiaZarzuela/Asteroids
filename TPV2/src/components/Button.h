
#pragma once
#include "FramedImage.h"
#include "TextRender.h"
#include "Transform.h"
#include "../ecs/Component.h"
#include <functional>
#include "../ecs/Manager.h"

class Button : public Component {
private:
	int texture;
	ecs::msgId funct;
public:
	constexpr static ecs::cmpId_type id = ecs::_BUTTON;

	Button(int t, ecs::msgId f) : Component(), texture(t), funct(f) {}
	void initComponent() override;
	int getTexture() { return texture; }
	ecs::msgId getFunction() { return funct; }
};

