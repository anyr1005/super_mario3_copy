#include "stdafx.h"
#include "goomba.h"

HRESULT goomba::init(EnemyState es, POINT position)
{
	enemy::init(es,position);

	_jumpCount = 1;
	_jumpPower = 2.0f;

	if (_state == ENEMY_LEFT_WALK || _state == ENEMY_RIGHT_WALK)
	{
		_image = IMAGEMANAGER->findImage("goomba_walk");
	}
	else if (_state == ENEMY_LEFT_JUMP || _state == ENEMY_RIGHT_JUMP)
	{
		_image = IMAGEMANAGER->findImage("goomba_wing");
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_collisonRange = RectMakeCenter(_x, _rc.bottom - 24, 48, 48);

	return S_OK;
}

void goomba::move()
{
	if (_state == ENEMY_LEFT_WALK || _state == ENEMY_RIGHT_WALK)
	{
		_image = IMAGEMANAGER->findImage("goomba_walk");
	}
	else if (_state == ENEMY_LEFT_JUMP || _state == ENEMY_RIGHT_JUMP)
	{
		_image = IMAGEMANAGER->findImage("goomba_wing");
	}
	else if (_state == ENEMY_DIE)
	{
		
		_image = IMAGEMANAGER->findImage("goomba_crush");
	}

	switch (_state)
	{
	case ENEMY_LEFT_WALK:
		_x -= ENEMYSPEED;
		break;
	case ENEMY_RIGHT_WALK:
		_x += ENEMYSPEED;
		break;
	case ENEMY_LEFT_JUMP:
		_y -= _jumpPower;
		_jumpPower -= GRAVITY;
		_x -= 2;
		break;
	case ENEMY_RIGHT_JUMP:
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


	//점프 상태일 때 점프 처리
	if ((_state == ENEMY_LEFT_JUMP || _state == ENEMY_RIGHT_JUMP) && _isOnGround)
	{
		_jumpCount++;
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

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_collisonRange = RectMakeCenter(_x, _rc.bottom - 24, 48, 48);
}

void goomba::draw()
{
	if (_isVisible)
	{
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _collisonRange);
	}
}
