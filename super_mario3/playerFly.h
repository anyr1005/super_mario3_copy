#pragma once
#include "playerState.h"
class playerFly : public playerState
{
private:
	int _count, _index;
	float _jumpPower;
	playerStateName _stateName;
	bool _isStart;
public:
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
	virtual playerStateName getStateName() { return _stateName; }
};

