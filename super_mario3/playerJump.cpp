#include "stdafx.h"
#include "playerJump.h"

playerState * playerJump::handleInput(player * player)
{
	return nullptr;
}

void playerJump::update(player * player)
{
	player->setY(player->getY() - _jumpPower);
	_jumpPower -= _gravity;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->setX(player->getX() - player->getRunSpeed());
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setX(player->getX() + player->getRunSpeed());
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
