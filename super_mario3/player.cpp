#include "stdafx.h"
#include "player.h"
#include "playerIdle.h"

HRESULT player::init()
{
	IMAGEMANAGER->addFrameImage("mario_walk", "img/mario/mario_walk.bmp", 90, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mario_skid", "img/mario/mario_skid.bmp", 42, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mario_run", "img/mario/mario_run.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mario_jump", "img/mario/mario_jump.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_isRight = true;

	_state = new playerIdle;
	_state->enter(this);

	_x = 100;
	_y = BACKGROUNDY - 72;
	
	_rc = RectMakeCenter(_x, _y, 45, 48);

	_runSpeed = BASICSPEED;
	
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	handleInput();
	_state->update(this);
	_rc = RectMakeCenter(_x, _y, 45, 48);
}

void player::render()
{
	_img->frameRender(getMemDC(), _rc.left, _rc.top);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
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

