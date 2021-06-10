#include "stdafx.h"
#include "koopa_troopa.h"

HRESULT koopa_troopa::init(EnemyState es, POINT position)
{
	enemy::init(es, position);
	_jumpPower = 6.0f;
	_isShell = false;

	if (_state == LEFT_WALK || _state == RIGHT_WALK)
	{
		_image = IMAGEMANAGER->findImage("green_walk");
	}
	else if (_state == LEFT_JUMP || _state == RIGHT_JUMP)
	{
		_image = IMAGEMANAGER->findImage("green_wing");
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	return E_NOTIMPL;
}

void koopa_troopa::move()
{
	if (_state == LEFT_WALK || _state == RIGHT_WALK)
	{
		_image = IMAGEMANAGER->findImage("green_walk");
	}
	else if (_state == LEFT_JUMP || _state == RIGHT_JUMP)
	{
		_image = IMAGEMANAGER->findImage("green_wing");
	}

	switch (_state)
	{
	case LEFT_WALK:
		_x -= ENEMYSPEED;
		break;
	case RIGHT_WALK:
		_x += ENEMYSPEED;
		break;
	case LEFT_JUMP:
		_y -= _jumpPower;
		_jumpPower -= GRAVITY;
		_x -= ENEMYSPEED;
		break;
	case RIGHT_JUMP:
		_y -= _jumpPower;
		_jumpPower -= GRAVITY;
		_x += ENEMYSPEED;
		break;
	default:
		break;
	}

	/*
		=====================================
		나중에 지워주기(충돌처리 후)
	*/
	if (_rc.left < 0)
	{
		_x = _image->getFrameWidth() / 2;
		if (_state == LEFT_JUMP)
		{
			_state = RIGHT_JUMP;
		}
		else
		{
			_state = RIGHT_WALK;
		}

	}

	if (_x >= _spawnX)
	{
		_x = _spawnX;
		if (_state == RIGHT_JUMP)
		{
			_state = LEFT_JUMP;
		}
		else
		{
			_state = LEFT_WALK;
		}
	}

	if (_y >= _spawnY)
	{
		_y = _spawnY;
		_jumpPower = 6.0f;
	}
	//=====================================
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	if (_state == LEFT_JUMP || _state == LEFT_WALK)
	{
		_currentFrameY = 0;
	}
	else
	{
		_currentFrameY = 1;
	}

	_count++;
	if (_count % 10 == 0)
	{
		if (_currentFrameX >= _image->getMaxFrameX()) _currentFrameX = 0;
		else _currentFrameX++;
		_image->setFrameX(_currentFrameX);

		_count = 0;
	}
}

void koopa_troopa::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}
