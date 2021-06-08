#pragma once
#include "playerState.h"
class playerFall : public playerState
{
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
};

