#include "Button.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/InputHandler.h"

void Button::initComponent() {
}
//
//void Button::handleInput() {
//    SDL_Point mousePosition;
//    SDL_Rect buttonRect = { (int)transform->getPos().getX(), (int)transform->getPos().getY(), (int)transform->getW(), (int)transform->getH() };
//    Vector2D position = transform->getPos();
//    Vector2D textPosition;
//    SDL_GetMouseState(&mousePosition.x, &mousePosition.y); 
//    if (!SDL_PointInRect(&mousePosition, &buttonRect)) {
//        textPosition = Vector2D(transform->getPos().getX() + (transform->getW() - text->getW()) / 2, transform->getPos().getY() + (transform->getH() - text->getH()) / 2 - 10);
//        texture->setCol(currentButtonFrame);
//        text->setPos(textPosition);
//        currentButtonFrame = MOUSE_OUT;
//    }
//
//    if (SDL_PointInRect(&mousePosition, &buttonRect) && (currentButtonFrame == MOUSE_OUT || currentButtonFrame == MOUSE_OVER)) {
//        textPosition = Vector2D(transform->getPos().getX() + (transform->getW() - text->getW()) / 2, transform->getPos().getY() + (transform->getH() - text->getH()) / 2 - 10);
//        texture->setCol(currentButtonFrame);
//        text->setPos(textPosition);
//        currentButtonFrame = MOUSE_OVER; 
//    }
//
//    if (SDL_PointInRect(&mousePosition, &buttonRect) && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) { 
//        currentButtonFrame = CLICKED;
//        textPosition = Vector2D(transform->getPos().getX() + (transform->getW() - text->getW()) / 2, transform->getPos().getY() + (transform->getH() - text->getH()) / 2);
//        texture->setCol(currentButtonFrame);
//        text->setPos(textPosition);
//    }
//
//    if (SDL_PointInRect(&mousePosition, &buttonRect) && currentButtonFrame == CLICKED && !InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) {
//        currentButtonFrame = MOUSE_OVER;
//        textPosition = Vector2D(transform->getPos().getX() + (transform->getW() - text->getW()) / 2, transform->getPos().getY() + (transform->getH() - text->getH()) / 2 - 10);
//        texture->setCol(currentButtonFrame);
//        text->setPos(textPosition);
//        onClick(); 
//    }
//}
//
//void Button::onClick() {
//    InputHandler::instance()->clearState(true);
//    callback();
//}