#pragma once
#include "player.h"

enum playerStateName
{
	PLAYER_IDLE,
	PLAYER_WALK,
	PLAYER_SLIP,
	PLAYER_SKID,
	PLAYER_JUMP,
	PLAYER_FALL,
	PLAYER_DIE,
	PLAYER_CHANGE,
	PLAYER_FLY,
	PLAYER_ATTACK
};

class player;
#define ACCEL 0.2f
#define BASICSPEED 5
#define SPEEDMAX 12
#define FRICTION 0.2f

class playerState
{
protected:
public:
	virtual playerState* handleInput(player * player) = 0;
	virtual void update(player * player) = 0;
	virtual void enter(player * player) = 0;
	virtual playerStateName getStateName() = 0;
};