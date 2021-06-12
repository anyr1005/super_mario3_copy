#include "stdafx.h"
#include "playerFly.h"
#include "playerIdle.h"

playerState * playerFly::handleInput(player * player)
{
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		return new playerFly;
	}
	if (player->getIsOnGround())
	{
		return new playerIdle;
	}
	return nullptr;
}

void playerFly::update(player * player)
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

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{

	}

	_count++;
	if (_count % 10 == 0)
	{
		if (_index >= player->getImage()->getMaxFrameX()) _index = 0;
		else _index++;
		player->getImage()->setFrameX(_index);
		if (player->getIsRight())
		{
			player->getImage()->setFrameY(1);
		}
		else
		{
			player->getImage()->setFrameY(0);
		}
	}
}

void playerFly::enter(player * player)
{
	_jumpPower = 6.0f;
	_stateName = PLAYER_FLY;
	player->setImage("tail_fly");
	_count = _index = 0;
}
