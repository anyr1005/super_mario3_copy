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
	_jumpPower -= GRAVITY;
	player->setJumpPower(_jumpPower);

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->setIsRight(false);
		player->setX(player->getX() - player->getRunSpeed());
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setIsRight(true);
		player->setX(player->getX() + player->getRunSpeed());
	}
}

void playerFall::enter(player * player)
{
	_jumpPower = -4.0f;
	player->setJumpPower(_jumpPower);
}