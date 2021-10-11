#pragma once
#include "playerState.h"
class playerJump : public playerState
{
private:

	float _jumpPower;
	playerStateName _stateName;

	bool _isLeftAir;
	bool _isRightAir;
	bool _isTurn;
public:
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
	virtual playerStateName getStateName() { return _stateName; }
};

