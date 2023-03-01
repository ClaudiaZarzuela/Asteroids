#pragma once
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "Transform.h"
#include "../ecs/Manager.h"
class Follow : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_FOLLOW;
	Follow(): tr_(nullptr), q(nullptr) {}
	virtual ~Follow();
	void initComponent() override;
	void update() override;

private:
	Transform* tr_;
	Transform* q;
};

