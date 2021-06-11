#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(EnemyState es, POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_count = 0;
	_state = es;
	_x = _spawnX = position.x;
	_y = _spawnY = position.y;

	_isVisible = true;
	_isOnGround = false;

	return S_OK;
}

void enemy::release()
{

}

void enemy::update()
{
	if (_state == ENEMY_LEFT_WALK || _state == ENEMY_RIGHT_WALK)
	{
		if (!_isOnGround)
		{
			_y -= _jumpPower;
			_jumpPower -= GRAVITY;
		}
		/*
		else
		{
			_jumpPower = -4.0f;
		}
		*/
	}
	move();
}

void enemy::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	draw();
}

