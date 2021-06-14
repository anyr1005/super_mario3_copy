#include "stdafx.h"
#include "playerSlip.h"

playerState * playerSlip::handleInput(player * player)
{
	if (player->getRunSpeed() < BASICSPEED)
	{
		player->setRunSpeed(BASICSPEED);
		return new playerIdle;
	}
	return nullptr;
}

void playerSlip::update(player * player)
{
	player->setRunSpeed(player->getRunSpeed() - FRICTION);

	if (player->getIsRight())
	{
		//¿À¸¥ÂÊ
		player->setX(player->getX() + player->getRunSpeed());
	}
	else
	{
		//¿ÞÂÊ
		player->setX(player->getX() - player->getRunSpeed());
	}
	
	if (!player->getIsOnGround())
	{
		player->setY(player->getY() - _jumpPower);
		_jumpPower -= GRAVITY;
		player->setJumpPower(_jumpPower);
	}

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

void playerSlip::enter(player * player)
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

	if (player->getIsRight())
	{
		player->getImage()->setFrameY(1);
	}
	else
	{
		player->getImage()->setFrameY(0);
	}
	_count = _index = 0;
	_jumpPower = -4.0f;
	_stateName = PLAYER_SLIP;
}
