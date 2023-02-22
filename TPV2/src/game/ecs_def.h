#pragma once
#include <cstdint>

namespace ecs { //not sure

	using cmpId_type = uint8_t;
	enum cmpId : cmpId_type {
		_TRANSFORM = 0,
		_IMAGE,
		_CTRL,
		_OPPOSITESIDE,
		_DEACCELERATION,
		// do not remove this
		_LAST_CMP_ID
	};
	constexpr cmpId_type maxComponentId = _LAST_CMP_ID;
	using grpId_type = uint8_t;
	enum grpId : grpId_type {
		_grp_ASTEROIDS,
		_grp_GENERAL,
		//...
		_LAST_GRP_ID
	};
	constexpr grpId_type maxGroupId = _LAST_GRP_ID;
	//...
}
