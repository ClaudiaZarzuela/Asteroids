#pragma once
#include "../checkML.h"
#include "Transform.h"
// componente que reduce la velocidad del caza gradualmente
struct DeAcceleration : public Component
{
public:
	// id 
	constexpr static ecs::cmpId_type id = ecs::_DEACCELERATION;
	// metodos publicos de la clase
	DeAcceleration() : tr_(nullptr){}
	virtual ~DeAcceleration();
	void initComponent() override;

private:
	Transform* tr_;
};

