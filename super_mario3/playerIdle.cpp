#include "stdafx.h"
#include "playerIdle.h"
#include "playerWalk.h"

playerState* playerIdle::handleInput(player * player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//걷는 상태로 바꾸기
		return new playerWalk;
	}
	return nullptr;
}

void playerIdle::update(player* player)
{
	player->getImage()->setFrameX(0);
	player->getImage()->setFrameY(0);
}

void playerIdle::enter(player* player)
{
	player->setImage("mario_walk");
	_count = 0;
}
