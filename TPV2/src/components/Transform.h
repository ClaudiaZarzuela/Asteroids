#pragma once
class Transform : public ecs::Component {
public:
	Transform(…) : …{ … }
		virtual ~Transform() …
		inline Vector2D& getPos() …
		inline Vector2D& getVel() …
		…
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

