#pragma once
#include "Transform.h"
#include "../sdlutils/Texture.h"
class FramedImage: public Component
{
public: 
	constexpr static ecs::cmpId_type id = ecs::_IMAGE;
	FramedImage(Texture* tex) : tr_(nullptr), tex_(tex){
		 row = tex_->getRow();
		 col = tex_->getCol();
	}
	virtual ~FramedImage();
	void initComponent() override;
	void render() override;
private:
	Transform* tr_;
	Texture* tex_;
	int row = 0;
	int col = 0;
};

