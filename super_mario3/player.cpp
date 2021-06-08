#include "stdafx.h"
#include "player.h"
#include "playerIdle.h"

HRESULT player::init()
{
	IMAGEMANAGER->addFrameImage("mario_walk", "img/mario/mario_walk.bmp", 90, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mario_skid", "img/mario/mario_skid.bmp", 42, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mario_run", "img/mario/mario_run.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mario_jump", "img/mario/mario_jump.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mario_run_jump", "img/mario/mario_run_jump.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_isRight = true;

	_state = new playerIdle;
	_state->enter(this);

	_x = 100;
	_y = BACKGROUNDY - 72;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_runSpeed = BASICSPEED;

	_isLRCollison = false;
	_isOnGround = true;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	collisonGround();
	collisonObject();
	collisonPipe();
	handleInput();
	_state->update(this);
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void player::render()
{
	_img->frameRender(getMemDC(), _rc.left, _rc.top);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);

		char str[128];
		sprintf_s(str, "%d", _img->getFrameWidth());
		TextOut(getMemDC(), _x, _y, str, strlen(str));
	}
}


void player::handleInput()
{
	playerState* state = _state->handleInput(this);
	if (state != NULL)
	{
		SAFE_DELETE(_state);
		_state = state;
		_state->enter(this);
	}

}

void player::collisonGround()
{
	_isLRCollison = false;
	_isOnGround = false;
	for (int i = 0; i < _mManager->getGround().size(); i++)
	{
		RECT temp;
		RECT ground = _mManager->getGround()[i];
		if (IntersectRect(&temp, &ground, &_rc))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			//상하 충돌
			if (width > height)
			{
				//위에서 아래로 충돌
				if ((_rc.top + _rc.bottom) / 2 < (ground.top + ground.bottom) / 2)
				{
					_y -= height;
					_state = new playerIdle;
					_state->enter(this);
					_isOnGround = true;
				}
			}
			//좌우 충돌
			else
			{
				_isLRCollison = true;
				//왼쪽에서 충돌
				if ((_rc.left + _rc.right) / 2 < (ground.left + ground.right) / 2)
				{
					_x -= width;
				}
				//오른쪽에서 충돌
				else
				{
					_x += width;
				}
			}
		}
	}
}

void player::collisonObject()
{
	_isOnGround = false;
	for (int i = 0; i < _mManager->getObject().size(); i++)
	{
		RECT temp;
		RECT object = _mManager->getObject()[i];
		if (IntersectRect(&temp, &object, &_rc))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			//상하 충돌
			if (width > height)
			{
				//위에서 아래로 충돌
				if ((_rc.top + _rc.bottom) / 2 < (object.top + object.bottom) / 2 && _jumpPower < 0)
				{
					_y -= height;
					_state = new playerIdle;
					_state->enter(this);
					_isOnGround = true;
					break;
				}
				//아래에서 충돌처리 없음
			}
			//좌우 충돌 없음
		}
	}
}

void player::collisonPipe()
{
	_isOnGround = false;
	_isLRCollison = false;
	for (int i = 0; i < _mManager->getPipe().size(); i++)
	{
		RECT temp;
		RECT head = _mManager->getPipe()[i].head;
		if (IntersectRect(&temp, &head, &_rc))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			//상하 충돌
			if (width > height)
			{
				//위에서 아래로 충돌
				if ((_rc.top + _rc.bottom) / 2 < (head.top + head.bottom) / 2 && _jumpPower < 0)
				{
					_y -= height;
					_state = new playerIdle;
					_state->enter(this);
					_isOnGround = true;
					break;
				}
				else
				{
					_y += height;
					break;
				}
			}
			//좌우 충돌
			else
			{
				_isLRCollison = true;
				//왼쪽에서 충돌
				if ((_rc.left + _rc.right) / 2 < (head.left + head.right) / 2)
				{
					_x -= width;
					break;
				}
				//오른쪽에서 충돌
				else
				{
					_x += width;
					break;
				}
			}
		}
	}
	for (int i = 0; i < _mManager->getPipe().size(); i++)
	{
		RECT temp;
		RECT body = _mManager->getPipe()[i].body;
		if (IntersectRect(&temp, &body, &_rc))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			//좌우 충돌(상하 충돌 없음)
			if (width <= height)
			{
				_isLRCollison = true;
				//왼쪽에서 충돌
				if ((_rc.left + _rc.right) / 2 < (body.left + body.right) / 2)
				{
					_x -= width;
					break;
				}
				//오른쪽에서 충돌
				else
				{
					_x += width;
					break;
				}
			}
		}
	}
	
}



