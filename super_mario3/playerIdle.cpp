#include "stdafx.h"
#include "playerIdle.h"
#include "playerWalk.h"
#include "playerJump.h"

playerState* playerIdle::handleInput(player * player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->setIsRight(false);
		//걷는 상태로 바꾸기
		return new playerWalk;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setIsRight(true);
		//걷는 상태로 바꾸기
		return new playerWalk;
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		return new playerJump;
	}
	return nullptr;
}

void playerIdle::update(player* player)
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
	if (!player->getIsOnGround())
	{
		player->setY(player->getY() - _jumpPower);
		_jumpPower -= GRAVITY;
		player->setJumpPower(_jumpPower);
	}
}

void playerIdle::enter(player* player)
{
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
	_count = 0;
	_jumpPower = -4.0f;
	_stateName = PLAYER_IDLE;
}
