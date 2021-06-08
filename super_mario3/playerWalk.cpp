#include "stdafx.h"
#include "playerWalk.h"
#include "playerRun.h"
#include "playerSlip.h"

playerState * playerWalk::handleInput(player * player)
{
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		return new playerSlip;
	}
	if (player->getRunSpeed() >= SPEEDMAX)
	{
		return new playerRun;
	}
	return nullptr;
}

void playerWalk::update(player * player)
{
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
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		player->setRunSpeed(player->getRunSpeed()+ACCEL);
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

void playerWalk::enter(player * player)
{
	player->setImage("mario_walk");
	_count = _index = 0;
}
