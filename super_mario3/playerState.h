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
	PLAYER_GROW,
	PLAYER_SHRINK,
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
	int _count, _index;
	float _jumpPower;
	playerStateName _stateName;
public:
	virtual playerState* handleInput(player * player) { return nullptr; }
	virtual void update(player * player) {}
	virtual void enter(player * player) {}
	playerStateName getStateName() { return _stateName; }
};