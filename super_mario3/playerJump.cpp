#include "stdafx.h"
#include "playerJump.h"
#include "playerIdle.h"

playerState * playerJump::handleInput(player * player)
{
	if (player->getIsOnGround())
	{
		return new playerIdle;
	}
	return nullptr;
}

void playerJump::update(player * player)
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
}
