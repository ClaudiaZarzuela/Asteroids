#pragma once
#include <list>
#include <windows.h>
#include "../src/ecs/Entity.h"
#include "../src/sdlutils/Texture.h"
#include "../src/utils/Vector2D.h"
#include "../src/ecs/Manager.h"
#include "../src/components/StateInput.h"


using namespace std;

// Clase GAMESTATE
class GameState
{
protected:
	// Constructora protegida
	Manager* manager_ ;
	Entity* inputCheck;
	GameState() { 
		manager_ = new Manager(); 
		inputCheck = manager_->addEntity();
		inputCheck->addComponent<StateInput>();
	};
	bool deleted = false;

public:

	// Destructora de la clase
	virtual ~GameState(){};

	// Metodos publicos de la clase
	void deleteState() { deleted = true; };
	virtual void update();
	virtual void refresh();
	virtual void render() const;
	virtual void changeState() {};

	// Getters
	virtual string getStateID() const = 0;
};

