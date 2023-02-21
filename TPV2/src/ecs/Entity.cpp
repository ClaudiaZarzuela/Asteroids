#include "Entity.h"
#include "Manager.h"

Entity::Entity() : mngr_(Manager::instance()), cmps_(), currCmps_(), alive_() {
	currCmps_.reserve(ecs::maxComponentId);
};