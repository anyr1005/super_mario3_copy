#pragma once
#include "playerIdle.h"
class playerSlip : public playerState
{
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
};

