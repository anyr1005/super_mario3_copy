#include "stdafx.h"
#include "playerWalk.h"
#include "playerSlip.h"
#include "playerSkid.h"
#include "playerJump.h"
#include "playerAttack.h"

playerState * playerWalk::handleInput(player * player)
{
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
	
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		return new playerJump;
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (player->getPlayerShape() == TAIL)
		{
			return new playerAttack;
		}
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
	if (KEYMANAGER->isStayKeyDown('Z') && !player->getIsLRCollison())
	{
		player->setRunSpeed(player->getRunSpeed()+ACCEL);
		if (player->getRunSpeed() > SPEEDMAX) player->setRunSpeed(SPEEDMAX);
	}
	else if (player->getRunSpeed() > BASICSPEED)
	{
		player->setRunSpeed(player->getRunSpeed() - FRICTION);
		if (player->getRunSpeed() < BASICSPEED) player->setRunSpeed(BASICSPEED);
	}

	if (player->getRunSpeed() < BASICSPEED)
	{
		player->setRunSpeed(player->getRunSpeed() + ACCEL);
	}

	if (player->getRunSpeed() >= SPEEDMAX)
	{
		switch (player->getPlayerShape())
		{
		case BASIC:
			player->setImage("mario_run");
			break;
		case SUPER:
			player->setImage("super_run");
			break;
		case TAIL:
			player->setImage("tail_run");
			break;
		default:
			break;
		}
	}
	else
	{
		switch (player->getPlayerShape())
		{
		case BASIC:
			player->setImage("mario_walk");
			break;
		case SUPER:
			player->setImage("super_walk");
			break;
		case TAIL:
			player->setImage("tail_walk");
			break;
		default:
			break;
		}
	}
	if (!player->getIsOnGround())
	{
		player->setY(player->getY() - _jumpPower);
		_jumpPower -= GRAVITY;
		player->setJumpPower(_jumpPower);
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
	switch (player->getPlayerShape())
	{
	case BASIC:
		player->setImage("mario_walk");
		break;
	case SUPER:
		player->setImage("super_walk");
		break;
	case TAIL:
		player->setImage("tail_walk");
		break;
	default:
		break;
	}
	_count = _index = 0;
	_jumpPower = -4.0f;
}
