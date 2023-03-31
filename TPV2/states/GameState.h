#pragma once
#include "../src/checkML.h"
#include <list>
#include <windows.h>
#include "../src/ecs/Entity.h"
#include "../src/sdlutils/Texture.h"
#include "../src/utils/Vector2D.h"
#include "../src/ecs/Manager.h"
#include "../src/sdlutils/InputHandler.h"
#include <string>

//using namespace std;

// Clase GAMESTATE
class GameState {
protected:
	int x, y;
	// Constructora protegida
	Manager* manager_;
	//InputHandler* input_ = nullptr;
	GameState();
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
	void setInputChangeState(bool b) { inputChangeState = b; }

	// Getters
	virtual std::string getStateID() const {}
};

