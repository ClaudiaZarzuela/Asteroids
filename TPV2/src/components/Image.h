#pragma once
#include "../sdlutils/Texture.h"
#include "Transform.h"

class Image : public Component {
public:
	constexpr static ecs::cmpId_type id = ecs::_IMAGE;
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


