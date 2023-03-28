#pragma once
#include "../checkML.h"
#include "Transform.h"

// componente que se encarga de mostrar la nave por el lado opuesto cuando esta sale de los limites de la pantalla
struct ShowAtOppositeSide: public Component
{
public:
	// id
	constexpr static ecs::cmpId_type id = ecs::_OPPOSITESIDE;
	//metodos publicos de la clase
	ShowAtOppositeSide() : tr_(nullptr){};
	virtual ~ShowAtOppositeSide();
	void initComponent() override;

private:
	Transform* tr_;
};

