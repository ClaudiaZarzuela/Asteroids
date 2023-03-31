#pragma once
#include "../checkML.h"
#include "../utils/Vector2D.h"
#include <cstdint>

class Entity;
// definicion del namespace ecs que contiene los enumerados de Id de componentes, grupos y handlers
namespace ecs {

	using cmpId_type = uint8_t;
	enum cmpId : cmpId_type {
		_TRANSFORM = 0,
		_IMAGE,
		_CTRL,
		_OPPOSITESIDE,
		_DEACCELERATION,
		_HEALTH,
		_GUN,
		_ONEXIT,
		_FOLLOW,
		_GENERATIONS,
		_RENDERTEXT,
		_LAST_CMP_ID
	};
	constexpr cmpId_type maxComponentId = _LAST_CMP_ID;
	using grpId_type = uint8_t;
	enum grpId : grpId_type {
		_grp_ASTEROIDS,
		_grp_GENERAL,
		_grp_BULLETS,
		_grp_TEXT,
		_LAST_GRP_ID
	};
	constexpr grpId_type maxGroupId = _LAST_GRP_ID;
	using hdlrId_type = uint8_t;
	enum hdlrId : hdlrId_type { 
		FIGHTER,
		_LAST_HDLR_ID };
	constexpr hdlrId_type maxHdlrId = _LAST_HDLR_ID;
	using sysId_type = uint8_t;
	enum sysId : sysId_type {
		_sys_CNTRL,
		_sys_ASTEROIDS,
		_sys_FIGHTER,
		_sys_BULLETS,
		_sys_COLLISIONS,
		_LAST_SYS_ID
	};
	constexpr sysId_type maxSysId = _LAST_SYS_ID;

	using msgId_type = uint8_t;
	struct Message {
		msgId_type id;
		// _m_STAR_EATEN
		struct {
			Entity* e;
		} star_eaten_data;
		// _m_ADD_STARS
		struct {
			unsigned int n;
		} add_stars_data;

		struct {
			Vector2D pos;
			Vector2D vel;
			double rot;
			int width;
			int height;
		} bullet_data;
	};
	enum msgId : msgId_type {
		//_m_STAR_EATEN, //
		_m_STAR_SHOT,
		_m_FIGHTER_CRASHED,
		_m_LEFT,
		_m_RIGHT,
		_m_UP,
		_m_SHOOT,
		_m_ROUND_OVER,
		_m_ROUND_START,
		_m_CHANGE_STATE
	};
}
