#pragma once
#include "../checkML.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"

// componente encargado de renderizar texturas con varios frames paar formar una animacion
struct FramedImage: public Component
{
public:
	// id
	constexpr static ecs::cmpId_type id = ecs::_IMAGE;
	// metodos publicos de la clase
	FramedImage(Texture* tex) : tr_(nullptr), tex_(tex) {}
	virtual ~FramedImage();
	void initComponent() override;
	int getCol() { return col; }
	int getRow() { return row; }
	
private:
	Transform* tr_;
	Texture* tex_;
	int row = 0;
	int col = 0;
	int frameTime = 0;
};

