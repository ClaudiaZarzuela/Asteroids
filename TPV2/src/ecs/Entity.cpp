#include "Entity.h"
#include "Manager.h"

Entity::Entity(Manager* m) : mngr_(m), cmps_(), currCmps_(), alive_() {
	currCmps_.reserve(ecs::maxComponentId);
};