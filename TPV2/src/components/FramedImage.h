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
	FramedImage() {}
	virtual ~FramedImage();
	void initComponent() override;
	int getCol() { return col; }
	int getRow() { return row; }
	void setRow(int r) { row = r; }
	void setCol(int c) { col = c; }
	
private:
	int row = 0;
	int col = 0;
	int frameTime = 0;
};

