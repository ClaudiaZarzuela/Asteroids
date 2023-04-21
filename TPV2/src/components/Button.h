
#pragma once
#include "FramedImage.h"
#include "TextRender.h"
#include "Transform.h"
#include "../ecs/Component.h"
#include <functional>
#include "../ecs/Manager.h"

class Button : public Component {
private:
	enum button_ID {MULTIPLAYER_ = 0, SINGLEPLAYER_ =1, HOST_ =2, CLIENT_ =3 }; 
	button_ID ID;

public:
	constexpr static ecs::cmpId_type id = ecs::_BUTTON;

	Button(int id) : Component(), ID((button_ID)id) {}
	void initComponent() override;
};

