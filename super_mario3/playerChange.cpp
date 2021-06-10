#include "stdafx.h"
#include "playerChange.h"
#include "playerIdle.h"

playerState * playerChange::handleInput(player * player)
{
	if (_index >= player->getImage()->getMaxFrameX())
	{
		switch (player->getPlayerShape())
		{
		case BASIC:
			player->setPlayerShape(SUPER);
			break;
		case SUPER:
			player->setPlayerShape(TAIL);
			break;
		default:
			break;
		}
		return new playerIdle;
	}


	return nullptr;
}

void playerChange::update(player * player)
{
	_count++;
	if (_count % 5 == 0)
	{
		if (_index >= player->getImage()->getMaxFrameX()) _index = player->getImage()->getMaxFrameX();
		else _index++;
		player->getImage()->setFrameX(_index);
		if (player->getPlayerShape() == BASIC)
		{
			if (player->getIsRight())
			{
				player->getImage()->setFrameY(1);
			}
			else
			{
				player->getImage()->setFrameY(0);
			}
		}
		else if (player->getPlayerShape() == SUPER)
		{
			player->getImage()->setFrameY(0);
		}
	}
}

void playerChange::enter(player * player)
{
	switch (player->getPlayerShape())
	{
	case BASIC:
		player->setImage("mario_grow");
		break;
	case SUPER:
		player->setImage("mario_change");
		break;
	default:
		break;
	}
	_count = _index = 0;
}