#include "stdafx.h"
#include "playerFall.h"
#include "playerIdle.h"

playerState * playerFall::handleInput(player * player)
{
	if (player->getIsOnGround())
	{
		return new playerIdle;
	}
	return nullptr;
}

void playerFall::update(player * player)
{
	player->setY(player->getY() - _jumpPower);
	_jumpPower -= _gravity;
	player->setJumpPower(_jumpPower);
}

void playerFall::enter(player * player)
{
	_jumpPower = -4.0f;
	player->setJumpPower(_jumpPower);
	_gravity = 0.2f;
}
