#pragma once
#include "player.h"

class player;
#define ACCEL 0.1f
#define BASICSPEED 5
#define SPEEDMAX 12

class playerState
{
protected:
	int _count, _index;
	bool _isRight;
public:
	virtual playerState* handleInput(player * player) { return nullptr; }
	virtual void update(player * player) {}
	virtual void enter(player * player) {}
};