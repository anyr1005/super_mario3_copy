#include "stdafx.h"
#include "playerAttack.h"
#include "playerIdle.h"
#include "playerWalk.h"

playerState * playerAttack::handleInput(player * player)
{
	if (_index >= player->getImage()->getMaxFrameX())
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			return new playerWalk;
		}
		return new playerIdle;
	}
	return nullptr;
}

void playerAttack::update(player * player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->setX(player->getX() - player->getRunSpeed());
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setX(player->getX() + player->getRunSpeed());
	}

	_count++;
	if (_count % 5 == 0)
	{
		if (_index >= player->getImage()->getMaxFrameX()) _index = player->getImage()->getMaxFrameX();
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


void playerAttack::enter(player * player)
{
	player->setImage("tail_attack");
	_count = _index = 0;
	_stateName = PLAYER_ATTACK;

	if (player->getIsRight())
	{
		player->getImage()->setFrameY(1);
	}
	else
	{
		player->getImage()->setFrameY(0);
	}
}
