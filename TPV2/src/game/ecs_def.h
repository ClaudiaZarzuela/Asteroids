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
		_BUTTON,
		_GENERATIONS,
		_RENDERTEXT,
		_LAST_CMP_ID
	};
	constexpr cmpId_type maxComponentId = _LAST_CMP_ID;
	using grpId_type = uint8_t;
	enum grpId : grpId_type {
		_grp_ASTEROIDS,
		_grp_GENERAL,
		_grp_PLAYERS,
		_grp_BULLETS,
		_grp_ENEMY_BULLETS,
		_grp_TEXT,
		_grp_BUTTONS,
		_LAST_GRP_ID
	};
	constexpr grpId_type maxGroupId = _LAST_GRP_ID;
	using hdlrId_type = uint8_t;
	enum hdlrId : hdlrId_type { 
		FIGHTER,
		PLAYER1,
		PLAYER2,
		_LAST_HDLR_ID };
	constexpr hdlrId_type maxHdlrId = _LAST_HDLR_ID;
	using sysId_type = uint8_t;
	enum sysId : sysId_type {
		_sys_CNTRL,
		_sys_ASTEROIDS,
		_sys_FIGHTER,
		_sys_BULLETS,
		_sys_COLLISIONS,
		_sys_RENDER,	
		_sys_BUTTON,
		_sys_ONLINE,
		_LAST_SYS_ID
	};
	constexpr sysId_type maxSysId = _LAST_SYS_ID;

	using msgId_type = uint8_t;
	enum msgId : msgId_type {
		//_m_STAR_EATEN, //
		_m_STAR_SHOT,
		_m_FIGHTER_CRASHED,
		_m_SHOOT,
		_m_STAR_EXTINCTION,
		_m_ROUND_START,
		_m_ROUND_OVER,
		_m_RESTART,
		_m_PLAY,
		_m_PAUSE,
		_m_CONTINUE,
		_m_GAME_OVER_WIN,
		_m_GAME_OVER_LOSE,
		_m_MAINMENU,
		_m_GAMEMODE,
		_m_ONLINE,
		_m_SINGLEPLAYER,
		_m_WAITING,
		_m_ONLINEPLAY,
		_m_HOST,
		_m_CLIENT,
		_m_CHANGE_STATE,
		_m_START_ONLINE_ROUND,
		_m_SHIP_MOVED,
		_m_ENEMY_MOVED,
		_m_ENEMY_BULLET
	};

	struct Message {
		msgId_type id;
		// _m_STAR_EATEN
		struct {
			Entity* bullet;
			Entity* asteroid;

		}star_shot_data;
		// _m_ADD_STARS
		struct{
			unsigned int n;
		}add_stars_data;

		struct {
			Entity* a;
		}star_crashed_data;

		struct {
			Vector2D pos;
			Vector2D vel;
			double rot;
			int width;
			int height;
		} bullet_data;

		struct{
			std::string hostName;
			std::string clientName;
		}player_name_data;

		struct {
			float x;
			float y;
			float rot;
			bool moving;
		}ship_movement_data;
	};
}
