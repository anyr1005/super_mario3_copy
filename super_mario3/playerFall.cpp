#include "stdafx.h"
#include "playerFall.h"
#include "playerIdle.h"
#include "playerWalk.h"

playerState * playerFall::handleInput(player * player)
{
	if (player->getIsOnGround() && (KEYMANAGER->isStayKeyDown(VK_LEFT)|| KEYMANAGER->isStayKeyDown(VK_RIGHT)))
	{
		return new playerWalk;
	}
	else if (player->getIsOnGround())
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
	/*
	if (_isFrame)
	{
		_count++;
		if (_count % 5 == 0)
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
	else
	{
		player->getImage()->setFrameX(0);
		if (player->getIsRight())
		{
			player->getImage()->setFrameY(1);
		}
		else
		{
			player->getImage()->setFrameY(0);
		}
	}
	*/
}

void playerFall::enter(player * player)
{
	_jumpPower = -4.0f;
	player->setJumpPower(_jumpPower);
	/*
	if (_stateName == PLAYER_WALK)
	{
		_isFrame = true;
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
	else if(_stateName == PLAYER_IDLE)
	{
		_isFrame = false;
		switch (player->getPlayerShape())
		{
		case BASIC:
			player->setImage("mario_idle");
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
	*/
	_stateName = PLAYER_FALL;

	if (player->getIsRight())
	{
		player->getImage()->setFrameY(1);
	}
	else
	{
		player->getImage()->setFrameY(0);
	}
	_count = _index = 0;
}
