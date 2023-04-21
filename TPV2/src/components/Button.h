
#pragma once
#include "FramedImage.h"
#include "TextRender.h"
#include "Transform.h"
#include "../ecs/Component.h"
#include <functional>
#include "../ecs/Manager.h"

class Button : public Component {
private:
	int ID;

public:
	constexpr static ecs::cmpId_type id = ecs::_BUTTON;

	Button(int id) : Component(), ID(id) {}
	void initComponent() override;
	int getID() { return ID; }
};

