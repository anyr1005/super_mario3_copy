#include "stdafx.h"
#include "playerRun.h"
#include "playerWalk.h"
#include "playerSkid.h"
#include "playerSlip.h"

playerState * playerRun::handleInput(player * player)
{
	if (player->getRunSpeed() < SPEEDMAX)
	{
		return new playerWalk;
	}
	
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->setIsRight(true);
			return new playerSkid;
		}
		return new playerSlip;
	}
	
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->setIsRight(false);
			return new playerSkid;
		}
		return new playerSlip;
	}

	return nullptr;

}

void playerRun::update(player * player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->setX(player->getX() - player->getRunSpeed());
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setX(player->getX() + player->getRunSpeed());
	}
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		player->setRunSpeed(player->getRunSpeed() + ACCEL);
		if (player->getRunSpeed() > SPEEDMAX) player->setRunSpeed(SPEEDMAX);
	}
	else if (player->getRunSpeed() > BASICSPEED)
	{
		player->setRunSpeed(player->getRunSpeed() - FRICTION);
		if (player->getRunSpeed() < BASICSPEED) player->setRunSpeed(BASICSPEED);
	}

	_count++;
	if (_count % 10 == 0)
	{
		if (player->getIsRight())
		{
			player->getImage()->setFrameY(1);
		}
		else
		{
			player->getImage()->setFrameY(0);
		}
		if (_index >= player->getImage()->getMaxFrameX()) _index = 0;
		else _index++;
		player->getImage()->setFrameX(_index);
	}
}

void playerRun::enter(player * player)
{
	player->setImage("mario_run");
	_count = _index = 0;
}
