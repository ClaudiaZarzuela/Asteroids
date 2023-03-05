#pragma once
#include "../checkML.h"
#include "Transform.h"
class DeAcceleration : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_DEACCELERATION;
	DeAcceleration():tr_(nullptr){}
	virtual ~DeAcceleration();
	void initComponent() override;
	void update() override;
private:
	Transform* tr_;
};

