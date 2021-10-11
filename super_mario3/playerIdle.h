#pragma once
#include "playerState.h"

class playerIdle : public playerState
{
private :
	float _jumpPower;
	playerStateName _stateName;

public:
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
	virtual playerStateName getStateName() { return _stateName; }
};

