#pragma once
#include "../checkML.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

// componente encargado de renderizar texturas
class Image : public Component {
public:
	// id
	constexpr static ecs::cmpId_type id = ecs::_IMAGE;
	// metodos publicos de la clase
	Image(Texture* tex) : 
		tr_(nullptr), 
		tex_(tex) {
	}
	virtual ~Image(); 
	void initComponent() override;
	void render() override;
private:
	Transform* tr_;
	Texture* tex_;
};


