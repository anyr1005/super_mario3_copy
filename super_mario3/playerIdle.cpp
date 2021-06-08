#include "stdafx.h"
#include "playerIdle.h"
#include "playerWalk.h"
#include "playerJump.h"

playerState* playerIdle::handleInput(player * player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->setIsRight(false);
		//�ȴ� ���·� �ٲٱ�
		return new playerWalk;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setIsRight(true);
		//�ȴ� ���·� �ٲٱ�
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
}

void playerIdle::enter(player* player)
{
	player->setImage("mario_walk");
	_count = 0;
}
