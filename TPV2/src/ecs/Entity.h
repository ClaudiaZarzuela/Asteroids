#pragma once

class Entity {
public:
	Entity();
	virtual ~Entity();
	inline void setContext(Manager* mngr) ...
		inline bool isAlive() …
		inline void setAlive(bool alive) …
		…
private:
	bool alive_;
	Manager* mngr_;
	std::vector<Component*> currCmps_;
	std::array<Component*, ecs::maxComponentId> cmps_;
};

