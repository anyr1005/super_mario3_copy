#include "stdafx.h"
#include "koopa_troopa.h"

HRESULT koopa_troopa::init(EnemyState es, POINT position)
{
	enemy::init(es, position);
	
	_isShell = false;

	switch (_state)
	{
	case ENEMY_LEFT_WALK:
	case ENEMY_RIGHT_WALK:
		_image = IMAGEMANAGER->findImage("green_walk");
		_jumpPower = -4.0f;
		break;
	case ENEMY_LEFT_JUMP:
	case ENEMY_RIGHT_JUMP:
		_image = IMAGEMANAGER->findImage("green_wing");
		_jumpPower = 6.0f;
		break;
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_collisonRange = RectMakeCenter(_rc.right - 13.5f, _rc.bottom - 36, 27, 36);
	return E_NOTIMPL;
}

void koopa_troopa::move()
{
	if (!_isShell)
	{
		//�̹��� ����
		switch (_state)
		{
		case ENEMY_LEFT_WALK:
		case ENEMY_RIGHT_WALK:
			_image = IMAGEMANAGER->findImage("green_walk");
			break;
		case ENEMY_LEFT_JUMP:
		case ENEMY_RIGHT_JUMP:
			_image = IMAGEMANAGER->findImage("green_wing");
			break;
		
		}
	}
	else
	{
		if (_state == ENEMY_ATTACKED)
		{
			_image = IMAGEMANAGER->findImage("green_shell_attacked");
		}
		else
		{
			_image = IMAGEMANAGER->findImage("green_shell");
		}
	}
	

	//������ ����
	switch (_state)
	{
	case ENEMY_LEFT_WALK:
		if (_isShell)
			_x -= 7;
		else
			_x -= ENEMYSPEED;
		
		break;
	case ENEMY_RIGHT_WALK:
		if (_isShell)
			_x += 7;
		else
			_x += ENEMYSPEED;
		break;
	case ENEMY_LEFT_JUMP:
		_y -= _jumpPower;
		_jumpPower -= GRAVITY;
		_x -= ENEMYSPEED;
		break;
	case ENEMY_RIGHT_JUMP:
		_y -= _jumpPower;
		_jumpPower -= GRAVITY;
		_x += ENEMYSPEED;
		break;
	case ENEMY_ATTACKED:
		_y -= _jumpPower;
		_jumpPower -= GRAVITY;
	break;
	default:
		break;
	}

	//jump�̸� ���� ����� �� �����Ŀ��ʱ�ȭ
	if (_isOnGround)
	{
		if (_state == ENEMY_LEFT_JUMP || _state == ENEMY_RIGHT_JUMP)
		{
			_jumpPower = 6.0f;
		}
		else if (_state == ENEMY_ATTACKED)
		{
			_jumpPower = 0;
		}
	}
	
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	
	//������(y) �� �浹 ��Ʈ ����
	switch (_state)
	{
	case ENEMY_LEFT_WALK:
	case ENEMY_LEFT_JUMP:
		_collisonRange = RectMakeCenter(_rc.right - 13.5f, _rc.bottom - 35, 27, 35);
		_currentFrameY = 0;
	break;
	case ENEMY_RIGHT_WALK:
	case ENEMY_RIGHT_JUMP:
		_collisonRange = RectMakeCenter(_rc.left + 13.5f, _rc.bottom - 35, 27, 35);
		if (_isShell)
		{
			_currentFrameY = 0;
		}
		else
		{
			_currentFrameY = 1;
		}
	break;
	case ENEMY_IDLE:
		_currentFrameY = 0;
	break;
	case ENEMY_ATTACKED:
		_currentFrameX = 0;
		_currentFrameY = 0;
	break;
	}

	if (_isShell)
	{
		_collisonRange = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}

	//shell�� ���� �ƴ� ��� ������(x) ����
	if (_isShell && _state == ENEMY_IDLE)
	{
		_currentFrameX = 0;
	}
	else
	{
		_count++;
		if (_count % 10 == 0)
		{
			if (_currentFrameX >= _image->getMaxFrameX()) _currentFrameX = 0;
			else _currentFrameX++;
			_image->setFrameX(_currentFrameX);

			_count = 0;
		}
	}
}

void koopa_troopa::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _collisonRange);
	}
}
