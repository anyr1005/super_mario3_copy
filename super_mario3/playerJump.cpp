#include "stdafx.h"
#include "playerJump.h"
#include "playerIdle.h"
#include "playerFly.h"
#include "playerAttack.h"

playerState * playerJump::handleInput(player * player)
{
	if (player->getIsOnGround())
	{
		return new playerIdle;
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (player->getRunSpeed() == SPEEDMAX && player->getPlayerShape() == TAIL)
		{
			return new playerFly;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		//꼬리 마리오 상태이면 공격
		if (player->getPlayerShape() == TAIL)
		{
			return new playerAttack;
		}
	}
	return nullptr;
}

void playerJump::update(player * player)
{

	player->setY(player->getY() - _jumpPower);
	_jumpPower -= GRAVITY;
	player->setJumpPower(_jumpPower);

	//이미지 재설정
	if (player->getRunSpeed() == SPEEDMAX)
	{
		switch (player->getPlayerShape())
		{
		case BASIC:
			player->setImage("mario_run_jump");
			break;
		case SUPER:
			player->setImage("super_run_jump");
			break;
		case TAIL:
			player->setImage("tail_run_jump");
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
	}
	else
	{
		switch (player->getPlayerShape())
		{
		case BASIC:
			player->setImage("mario_jump");
			break;
		case SUPER:
			player->setImage("super_jump");
			break;
		case TAIL:
			player->setImage("tail_jump");
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
	}

	if (_isRightAir)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->setRunSpeed(0.5f);
			player->setIsRight(false);
		}
		else
		{
			player->setX(player->getX() + player->getRunSpeed());
		}
		
	}
	if (_isLeftAir)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->setRunSpeed(0.5f);
			player->setIsRight(true);
		}
		else
		{
			player->setX(player->getX() - player->getRunSpeed());
		}
	}


	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (!_isLeftAir)
		{
			player->setIsRight(false);
			player->setX(player->getX() - player->getRunSpeed());
		}
	}


	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->setRunSpeed(0.1f);
			_isRightAir = _isLeftAir = false;
			player->setIsRight(true);
		}
		else
		{
			_isRightAir = true;
		}
	}
	

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (!_isRightAir)
		{
			player->setIsRight(true);
			player->setX(player->getX() + player->getRunSpeed());
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->setRunSpeed(0.1f);
			_isRightAir = _isLeftAir = false;
			player->setIsRight(false);
		}
		else
		{
			_isLeftAir = true;
		}
	}
	
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

void playerJump::enter(player * player)
{
	_jumpPower = 8.0f;
	player->setJumpPower(_jumpPower);
	if (player->getRunSpeed() == SPEEDMAX)
	{
		switch (player->getPlayerShape())
		{
		case BASIC:
			player->setImage("mario_run_jump");
			break;
		case SUPER:
			player->setImage("super_run_jump");
			break;
		case TAIL:
			player->setImage("tail_run_jump");
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
			player->setImage("mario_jump");
			break;
		case SUPER:
			player->setImage("super_jump");
			break;
		case TAIL:
			player->setImage("tail_jump");
			break;
		default:
			break;
		}
	}
	_stateName = PLAYER_JUMP;
	_isLeftAir = _isRightAir = false;
	_isTurn = false;
	if (player->getRunSpeed() < BASICSPEED)
	{
		player->setRunSpeed(BASICSPEED);
	}
}
