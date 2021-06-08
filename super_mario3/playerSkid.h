#pragma once
#include "playerState.h"
class playerSkid : public playerState
{
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
};

