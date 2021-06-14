#include "stdafx.h"
#include "playerDie.h"

playerState * playerDie::handleInput(player * player)
{
	return nullptr;
}

void playerDie::update(player * player)
{
	player->setY(player->getY() - _jumpPower);
	_jumpPower -= GRAVITY;
}

void playerDie::enter(player * player)
{
	player->setImage("mario_die");
	_jumpPower = 7.0f;
	_stateName = PLAYER_DIE;

	if (player->getIsRight())
	{
		player->getImage()->setFrameY(1);
	}
	else
	{
		player->getImage()->setFrameY(0);
	}
}
