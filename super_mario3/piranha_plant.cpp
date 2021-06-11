#include "stdafx.h"
#include "piranha_plant.h"

HRESULT piranha_plant::init(EnemyState es, POINT position)
{
	enemy::init(es, position);

	_image = IMAGEMANAGER->findImage("fire_red_left_down");
	_bodyImage = IMAGEMANAGER->findImage("long_leaf_green");
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_body = RectMakeCenter(_x, _y + _image->getHeight(), _bodyImage->getWidth(), _bodyImage->getHeight());
	return S_OK;
}

void piranha_plant::move()
{
	if (CAMERAMANAGER->getCameraLEFT() < _rc.right && CAMERAMANAGER->getCameraRIGHT() > _rc.left &&
		CAMERAMANAGER->getCameraTOP() < _rc.bottom && CAMERAMANAGER->getCameraBOTTOM() > _rc.top)
	{
		if (_spawnY - _y >= _image->getHeight() + _bodyImage->getHeight())
		{
			_y = _spawnY - (_image->getHeight() + _bodyImage->getHeight());
			_state = IDLE;
			_fireCount++;
		}
		else
		{
			_state = LEFT_WALK;
		}
	}
	else
	{
		_x = _spawnX;
		_y = _spawnY;
		_state = IDLE;
		_fireCount = 0;
	}

	switch (_state)
	{
	case LEFT_WALK:
		_y -= 2;
		break;
	case RIGHT_WALK:
		_y += 2;
		break;
	}

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_body = RectMakeCenter(_x, _y + _image->getHeight(), _bodyImage->getWidth(), _bodyImage->getHeight());
}

void piranha_plant::draw()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _body);
	}
	_image->render(getMemDC(), _rc.left, _rc.top);
	_bodyImage->render(getMemDC(), _body.left, _body.top);
}

bool piranha_plant::bulletCountFire()
{
	if (_fireCount % 150 == 0 && _state == IDLE && _spawnY != _y)
	{
		_fireCount = 0;
		return true;
	}
	return false;
}
