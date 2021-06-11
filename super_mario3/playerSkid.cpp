#include "stdafx.h"
#include "playerSkid.h"
#include "playerWalk.h"

playerState * playerSkid::handleInput(player * player)
{
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		player->setRunSpeed(BASICSPEED);
		return new playerIdle;
	}
	if (player->getRunSpeed() <= 0)
	{
		player->setRunSpeed(0);
		return new playerWalk;
	}
	return nullptr;
}

void playerSkid::update(player * player)
{
	player->setRunSpeed(player->getRunSpeed() - FRICTION * 2);

	player->getImage()->setFrameX(0);
	if (player->getIsRight())
	{
		//������ Ű�� ������ �������� �̲������� ����
		player->setX(player->getX() - player->getRunSpeed());
		player->getImage()->setFrameY(1);
	}
	else
	{
		//���� Ű�� ������ ���������� �̲������� ����
		player->setX(player->getX() + player->getRunSpeed());
		player->getImage()->setFrameY(0);
	}
	if (!player->getIsOnGround())
	{
		player->setY(player->getY() - _jumpPower);
		_jumpPower -= GRAVITY;
		player->setJumpPower(_jumpPower);
	}
}

void playerSkid::enter(player * player)
{
	_jumpPower = -4.0f;
	switch (player->getPlayerShape())
	{
	case BASIC:
		player->setImage("mario_skid");
		break;
	case SUPER:
		player->setImage("super_skid");
		break;
	case TAIL:
		player->setImage("tail_skid");
		break;
	default:
		break;
	}
	_stateName = PLAYER_SKID;
}
