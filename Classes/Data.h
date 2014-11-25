#pragma once
#include "cocos2d.h"
USING_NS_CC;



#define GRAVITY              Point(0,-980)
#define VELOCITY			 Point(0,260)	
#define THROUGH_PASS         160

typedef enum class state_enum{
	STATE_IDEL = 0,
	STATE_READY,
	STATE_GAME,
	STATE_CRASH
}PLANE_STATE;

typedef enum class random_color{
	BLUE = 0,
	GREEN,
	RED,
	YELLOW
}PLANE_COLOR;

typedef enum  state{
	LOGO = 0,
	MENU,
	READY,
	GAMING,
	OVER
}GAME_STATE;


typedef enum :uint8_t {
	COLLIDER_TYPE_PLANE = 0x1,
	COLLIDER_TYPE_LAND = 0x1 << 1,
	COLLIDER_TYPE_ROCK = 0x1 << 2
} COLLIDER_TYPE;

