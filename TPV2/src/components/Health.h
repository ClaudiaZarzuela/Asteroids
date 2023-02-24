#pragma once
#include "../sdlutils/Texture.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
class Health :public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_HEALTH;
	Health(Texture* tex, int h) :
		tex_(tex), maxLife(h) {
	}
	virtual ~Health();
	void render() override;
private:
	Texture* tex_;
	int maxLife;
};

