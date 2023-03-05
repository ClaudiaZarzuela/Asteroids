#pragma once
#include "../checkML.h"
#include "../ecs/Component.h"
#include "Transform.h"
#include<iostream>

using namespace std;
class DisableOnExit : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_ONEXIT;
	DisableOnExit() :tr_(nullptr) {}
	virtual ~DisableOnExit();
	void initComponent();
	void update() override;
private:
	Transform* tr_;
};

