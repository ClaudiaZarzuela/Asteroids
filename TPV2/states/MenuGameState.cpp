#include "MenuGameState.h"

// Constructora de la clase que define las proporciones del Dest_Rect de la textura de fondo
MenuGameState::MenuGameState() : GameState()
{
	//rectBack.x = 0; rectBack.y = 0; rectBack.w = WIN_WIDTH; rectBack.h = WIN_HEIGHT;
}

// Renderiza el fondo y llama al metodo de su padre
void MenuGameState::render() const {
	// Si falla el pause poner if de si background es igual a null
	if (background != nullptr)background->render(rectBack);
	GameState::render();
}
