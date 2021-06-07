#pragma once
#include "playerIdle.h"
class playerWalk : public playerState
{
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
};

