#pragma once
#include "player.h"

class player;
#define ACCEL 0.2f
#define BASICSPEED 5
#define SPEEDMAX 12
#define FRICTION 0.2f

class playerState
{
protected:
	int _count, _index;
public:
	virtual playerState* handleInput(player * player) { return nullptr; }
	virtual void update(player * player) {}
	virtual void enter(player * player) {}
};