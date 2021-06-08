#pragma once
#include "playerState.h"
class playerJump : public playerState
{
private:
	float _jumpPower, _gravity;
	bool isMove;
public:
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
};

