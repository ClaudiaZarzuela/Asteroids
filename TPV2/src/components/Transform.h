#pragma once
#include "../utils/Vector2D.h"
#include "../game/ecs_def.h"
#include "../ecs/Component.h"

class Transform : public ecs::Component {
public:
	constexpr static ecs::cmpId_type id = ecs::_TRANSFORM;

	Transform(/*...*/) :/*...*/{/*...*/};
	virtual ~Transform(); //...
	inline Vector2D& getPos(); //...
	inline Vector2D& getVel(); //...
	//...
private:
	Vector2D position_;
	Vector2D velocity_;
	float width_;
	float height_;
	float rotation_;

	/*A veces, el componente Transform
	tiene update con movimiento básico
	como pos_ = pos_ + vel_*/
};

