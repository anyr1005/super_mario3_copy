#pragma once
#include "playerState.h"

class playerIdle : public playerState
{
public:
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
};

