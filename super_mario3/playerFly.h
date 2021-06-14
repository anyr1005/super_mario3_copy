#pragma once
#include "playerState.h"
class playerFly : public playerState
{
private:
	bool _isStart;
public:
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
};

