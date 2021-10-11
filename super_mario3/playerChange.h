#pragma once
#include "playerState.h"
class playerChange : public playerState
{
private:
	int _count, _index;
	playerStateName _stateName;
public:
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
	virtual playerStateName getStateName() { return _stateName; }
};

