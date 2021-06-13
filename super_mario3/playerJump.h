#pragma once
#include "playerState.h"
class playerJump : public playerState
{
private:
	bool _isLeftAir;
	bool _isRightAir;
	bool _isTurn;
public:
	virtual playerState* handleInput(player * player);
	virtual void update(player * player);
	virtual void enter(player * player);
};

