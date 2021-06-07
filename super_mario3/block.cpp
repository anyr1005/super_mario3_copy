#include "stdafx.h"
#include "block.h"

HRESULT block::init()
{
	return S_OK;
}

HRESULT block::init(const char * imageName, POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_count = 0;

	_imageName = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(position.x, position.y,
		_imageName->getFrameWidth(), _imageName->getFrameHeight());


	return S_OK;
}

void block::release()
{
}

void block::update()
{
	_count++;
	if (_count % 10 == 0)
	{
		if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
		else _currentFrameX++;
		_imageName->setFrameX(_currentFrameX);
		

		_count = 0;
	}
}

void block::render()
{
	_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
}
