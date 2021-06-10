#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_count = 0;

	_image = IMAGEMANAGER->findImage(imageName);

	_x = position.x;
	_y = position.y;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{

	//상태패턴에 넣을것
	_count++;
	if (_count % 2 == 0)
	{
		_currentFrameX++;
		if (_currentFrameX >= _image->getMaxFrameX()) _currentFrameX = 0;
		_image->setFrameX(_currentFrameX);

		_count = 0;
	}
}

void enemy::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

