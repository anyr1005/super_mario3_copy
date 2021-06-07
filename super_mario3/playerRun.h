#pragma once
#include "playerIdle.h"

class playerRun : public playerState
{
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
};

