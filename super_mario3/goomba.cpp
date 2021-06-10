#include "stdafx.h"
#include "goomba.h"

HRESULT goomba::init(EnemyState es, POINT position)
{
	enemy::init(es,position);

	_jumpCount = 1;
	_jumpPower = 2.0f;

	if (_state == LEFT_WALK || _state == RIGHT_WALK)
	{
		_image = IMAGEMANAGER->findImage("goomba_walk");
	}
	else if (_state == LEFT_JUMP || _state == RIGHT_JUMP)
	{
		_image = IMAGEMANAGER->findImage("goomba_wing");
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

void goomba::move()
{
	if (_state == LEFT_WALK || _state == RIGHT_WALK)
	{
		_image = IMAGEMANAGER->findImage("goomba_walk");
	}
	else if (_state == LEFT_JUMP || _state == RIGHT_JUMP)
	{
		_image = IMAGEMANAGER->findImage("goomba_wing");
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
		_x -= 2;
		break;
	case RIGHT_JUMP:
		_y -= _jumpPower;
		_jumpPower -= GRAVITY;
		_x += 2;
		break;
	default:
		break;
	}

	_count++;
	if (_count % 10 == 0)
	{ 
		if (_currentFrameX >= _image->getMaxFrameX()) _currentFrameX = 0;
		else _currentFrameX++;
		_image->setFrameX(_currentFrameX);
		
		_count = 0;
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

	if (_x > _spawnX)
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
		_jumpCount++;
		_y = _spawnY;
		if (_jumpCount % 3 == 0)
		{
			_jumpPower = 5.0f;
			_jumpCount = 0;
		}
		else
		{
			_jumpPower = 3.0f;
		}
	}
	//=====================================
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void goomba::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}
