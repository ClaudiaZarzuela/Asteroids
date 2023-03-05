#pragma once
#include "../checkML.h"
#include "Transform.h"

class ShowAtOppositeSide: public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_OPPOSITESIDE;
	ShowAtOppositeSide():tr_(nullptr){};
	virtual ~ShowAtOppositeSide();
	void update() override;
	void initComponent() override;
private:
	Transform* tr_;
};

