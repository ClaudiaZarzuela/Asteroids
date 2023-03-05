#pragma once
#include "../src/checkML.h"
#include <list>
#include <windows.h>
#include "../src/ecs/Entity.h"
#include "../src/sdlutils/Texture.h"
#include "../src/utils/Vector2D.h"
#include "../src/ecs/Manager.h"
#include "../src/sdlutils/InputHandler.h"
#include "../src/components/TextRender.h"

using namespace std;

// Clase GAMESTATE
class GameState
{
protected:
	// Constructora protegida
	Manager* manager_ ;
	Entity* inputCheck = nullptr;
	GameState() { 
		manager_ = new Manager(); 
	};
	bool deleted = false;
	bool inputChangeState = false;

public:

	// Destructora de la clase
	virtual ~GameState(){
		delete manager_;
		manager_ = nullptr;
	};

	// Metodos publicos de la clase
	void deleteState() { deleted = true; };
	virtual void update();
	virtual void refresh();
	virtual void render() const;
	virtual void inputHandler();
	void setInputChangeState(bool b) { inputChangeState = b; }

	// Getters
	virtual string getStateID() const = 0;
};

