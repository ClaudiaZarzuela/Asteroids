#pragma once
#include "../checkML.h"
#include "../ecs/Component.h"
#include "Transform.h"
#include<iostream>

using namespace std;
// componente que desactiva las balas si estas salen de la pantalla
struct DisableOnExit : public Component
{
public:
	// id
	constexpr static ecs::cmpId_type id = ecs::_ONEXIT;
	// metodos publicos de la clase
	DisableOnExit() : tr_(nullptr) {}
	virtual ~DisableOnExit();
	void initComponent();

private:
	Transform* tr_;
};

