#pragma once

class Manager {
public:
	Manager();
	virtual ~Manager();
	Entity* addEntity();
	void refresh();
	void update();
	void render();
private:
	std::vector<Entity*> ents_;
	//hola
};

