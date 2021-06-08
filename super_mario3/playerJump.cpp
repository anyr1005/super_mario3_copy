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
	_jumpPower -= _gravity;
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
	_jumpPower = 9.0f;
	player->setJumpPower(_jumpPower);
	_gravity = 0.2f;
	if (player->getRunSpeed() == SPEEDMAX)
	{
		player->setImage("mario_run_jump");
	}
	else
	{
		player->setImage("mario_jump");
	}
}
