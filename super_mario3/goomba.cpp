#include "stdafx.h"
#include "goomba.h"

HRESULT goomba::init(POINT position)
{
	enemy::init(position);

	_image = new image;
	_image->init("img/goomba/goomba_walk.bmp", 96, 48, 2, 1, true, RGB(255, 0, 255));
	_state = LEFT_WALK;

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
