#include "../checkML.h"
#include "Transform.h"

void Transform::update(){
	position_ = position_ + velocity_;
}
