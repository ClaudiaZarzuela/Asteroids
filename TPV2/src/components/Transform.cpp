#include "../checkML.h"
#include "Transform.h"

// actualiza la posicion de la entidad segun su velocidad
void Transform::update(){
	position_ = position_ + velocity_;
}
