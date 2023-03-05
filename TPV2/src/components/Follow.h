#pragma once
#include "../checkML.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "Transform.h"
#include "../ecs/Manager.h"

// componente que hace que los asteoides dorados sigan a la nave
class Follow : public Component
{
public:
	// id
	constexpr static ecs::cmpId_type id = ecs::_FOLLOW;
	// metodos publicos de la clase
	Follow(): tr_(nullptr), q(nullptr) {}
	virtual ~Follow();
	void initComponent() override;
	void update() override;

private:
	Transform* tr_;
	Transform* q;
};

