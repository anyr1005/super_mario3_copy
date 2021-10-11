#pragma once
#include "playerIdle.h"
class playerWalk : public playerState
{
private:
	int _count, _index;
	float _jumpPower;
	playerStateName _stateName;

public:
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
	virtual playerStateName getStateName() { return _stateName; }
};

