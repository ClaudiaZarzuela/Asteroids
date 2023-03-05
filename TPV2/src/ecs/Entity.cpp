#include "../checkML.h"
#include "Entity.h"
#include "Manager.h"

// constructora
Entity::Entity(Manager* m) : mngr_(m), cmps_(), currCmps_(), alive_() {
	currCmps_.reserve(ecs::maxComponentId);
};