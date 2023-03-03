#pragma once
#include "../utils/Vector2D.h"
#include "../game/ecs_def.h"
#include "../ecs/Component.h"

class Transform : public Component {
public:
	constexpr static ecs::cmpId_type id = ecs::_TRANSFORM;

	Transform (Vector2D pos, Vector2D vel, float w, float h, float r): position_(pos), velocity_(vel), width_(w), height_(h), rotation_(r) {};
	virtual ~Transform() {}
	inline Vector2D& getPos() { return position_; }
	inline void setVel(Vector2D newVel) { velocity_ = newVel; }
	inline void setRot(float newRot) { rotation_ = newRot; }
	inline void setPos(Vector2D newPos) { position_ = newPos; }
	inline Vector2D& getVel() { return velocity_; }
	float getW() { return width_; }
	float getH() { return height_; }
	float getRot() { return rotation_; }
	void update() override;
private:
	Vector2D position_ = { 0, 0 };
	Vector2D velocity_ = { 0, 0 };
	float width_ = 0;
	float height_ = 0;
	float rotation_ = 0;

};

