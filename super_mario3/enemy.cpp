#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_count = 0;

	_x = _spawnX = position.x;
	_y = _spawnY = position.y;

	return S_OK;
}

void enemy::release()
{

}

void enemy::update()
{
	move();
}

void enemy::render()
{
	draw();
}

