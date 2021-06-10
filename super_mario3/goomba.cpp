#include "stdafx.h"
#include "goomba.h"

HRESULT goomba::init(EnemyState es, POINT position)
{
	enemy::init(es,position);

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
		_x -= ENEMYSPEED;
		break;
	case RIGHT_JUMP:
		_y -= _jumpPower;
		_x += ENEMYSPEED;
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

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void goomba::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}
