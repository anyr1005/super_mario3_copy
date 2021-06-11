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
	_state = _firstState = es;

	_x = _spawnX = position.x;
	_y = _spawnY = position.y;

	_isVisible = true;
	_isOnGround = false;
	_isAttacked = false;

	return S_OK;
}

void enemy::release()
{

}

void enemy::update()
{
	if (_state == ENEMY_LEFT_WALK || _state == ENEMY_RIGHT_WALK || _state == ENEMY_IDLE)
	{
		if (!_isOnGround)
		{
			_y -= _jumpPower;
			_jumpPower -= GRAVITY;
		}
		else
		{
			_jumpPower = -4.0f;
		}
	}

	if (_state == ENEMY_DIE)
	{
		if (!_isVisible && CAMERAMANAGER->getCameraLEFT() > _spawnX + _image->getFrameWidth() / 2)
		{
			_x = _spawnX;
			_y = _spawnY;
			_state = _firstState;
			_isVisible = true;
		}
		else
		{
			_deadCount++;
			if (_deadCount % 20 == 0)
			{
				_isVisible = false;
			}
		}
	}
	
	if (_rc.right < 0 || _rc.top > BACKGROUNDY)
	{
		_state = ENEMY_DIE;
	}

	move();
}

void enemy::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
		char str[128];
		sprintf_s(str, "xÁÂÇ¥ : %f", _x);
		TextOut(getMemDC(), _rc.left, _rc.top - 50, str, strlen(str));
		sprintf_s(str, "yÁÂÇ¥ : %f", _y);
		TextOut(getMemDC(), _rc.left, _rc.top - 30, str, strlen(str));
		sprintf_s(str, "jumpPower : %f", _jumpPower);
		TextOut(getMemDC(), _rc.left, _rc.top - 10, str, strlen(str));
	}
	draw();
}

