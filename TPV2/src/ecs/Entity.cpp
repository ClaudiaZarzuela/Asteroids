#include "../checkML.h"
#include "Entity.h"
#include "Manager.h"

// constructora
Entity::Entity(ecs::grpId_type gId): cmps_(), currCmps_(), alive_() {
	currCmps_.reserve(ecs::maxComponentId);
};