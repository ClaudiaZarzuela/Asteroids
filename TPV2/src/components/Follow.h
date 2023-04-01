#pragma once
#include "../checkML.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "Transform.h"

// componente que hace que los asteoides dorados sigan a la nave
struct Follow : public Component
{
public:
	// id
	constexpr static ecs::cmpId_type id = ecs::_FOLLOW;
	// metodos publicos de la clase
	Follow(){}
	virtual ~Follow();
	void initComponent() override;

};

