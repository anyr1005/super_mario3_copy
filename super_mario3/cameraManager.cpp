#include "stdafx.h"
#include "cameraManager.h"

void cameraManager::cameraRange()
{
	if (_cameraBuffer->getX() < 0) _cameraBuffer->setX(0);
	else if (_cameraBuffer->getX() + WINSIZEX > BACKGROUNDX)_cameraBuffer->setX(BACKGROUNDX - WINSIZEX);
	if (_cameraBuffer->getY() < 0)_cameraBuffer->setY(0);
	else if (_cameraBuffer->getY() + WINSIZEY > BACKGROUNDY) _cameraBuffer->setY(BACKGROUNDY - WINSIZEY);
}

HRESULT cameraManager::init()
{
	_cameraBuffer = new image;
	_cameraBuffer->init(WINSIZEX, WINSIZEY);
	_seeLine = false;
	for (int i = 0; i < 2; i++)
	{
		x[i] = 0;
		y[i] = 0;
	}
	return S_OK;
}

void cameraManager::release()
{
	SAFE_DELETE(_cameraBuffer);
}


void cameraManager::render(image* backBuffer, HDC frontDC)
{
	HDC cameraDC = _cameraBuffer->getMemDC();
	HDC backDC = backBuffer->getMemDC();

	if (_seeLine)
	{
		for (int i = 0; i < 2; i++)
		{
			if (x[i] != 0)
			{
				LineMake(backDC, x[i], _cameraBuffer->getY(), x[i], _cameraBuffer->getY() + WINSIZEY);
			}
			if (y[i] != 0)
			{
				LineMake(backDC, _cameraBuffer->getX(), y[i], _cameraBuffer->getX() + WINSIZEX, y[i]);
			}
		}
	}

	backBuffer->render(cameraDC, 0, 0, _cameraBuffer->getX(), _cameraBuffer->getY(), WINSIZEX, WINSIZEY);
	_cameraBuffer->render(frontDC, 0, 0);
}

void cameraManager::updateCamera(float x, float y)
{
	_cameraBuffer->setCenter(x, y);
	cameraRange();
}

void cameraManager::updateCamera(float x, float y, float ratioX, float ratioY)
{
	int cX, cY;
	if (ratioX > 0 && ratioY > 0 && ratioX < 1.0f && ratioY < 1.0f)
	{
		if (x == 0.5f)
		{
			cX = x;
		}
		else
		{
			cX = x - ratioX * WINSIZEX;
		}

		if (y == 0.5f)
		{
			cY = y;
		}
		else
		{
			cY = y - ratioY * WINSIZEY;
		}
		setCamera(cX, cY);
	}
	cameraRange();
}

void cameraManager::updateCamera(RECT& player, float ratioX, float ratioY)
{
	int width = player.right - player.left;
	int height = player.bottom - player.top;

	if (ratioX != 0)
	{
		if (ratioX < 0.5f)
		{
			if (player.left <= _cameraBuffer->getX() + ratioX * WINSIZEX)
			{
				_cameraBuffer->setX(player.left - ratioX * WINSIZEX);
			}
			if (player.right >= _cameraBuffer->getX() + WINSIZEX)
			{
				player.right = _cameraBuffer->getX() + WINSIZEX;
				player.left = player.right - width;
			}
		}
		else
		{
			if (player.right >= _cameraBuffer->getX() + ratioX * WINSIZEX)
			{
				_cameraBuffer->setX(player.right - ratioX * WINSIZEX);
			}
			if (player.left <= _cameraBuffer->getX())
			{
				player.left = _cameraBuffer->getX();
				player.right = player.left + width;
			}
		}
		x[0] = _cameraBuffer->getX() + ratioX * WINSIZEX;
		x[1] = 0;
	}

	if (ratioY != 0)
	{
		if (ratioY < 0.5f)
		{
			if (player.top <= _cameraBuffer->getY() + ratioY * WINSIZEY)
			{
				_cameraBuffer->setY(player.top - ratioY * WINSIZEY);
			}
			if (player.bottom >= _cameraBuffer->getY() + WINSIZEY)
			{
				player.bottom = _cameraBuffer->getY() + WINSIZEY;
				player.top = player.bottom - height;
			}
		}
		else
		{
			if (player.bottom >= _cameraBuffer->getY() + ratioY * WINSIZEY)
			{
				_cameraBuffer->setY(player.bottom - ratioY * WINSIZEY);
			}
			if (player.top <= _cameraBuffer->getY())
			{
				player.top = _cameraBuffer->getY();
				player.bottom = player.top + height;
			}
		}
		y[0] = _cameraBuffer->getY() + ratioY * WINSIZEY;
		y[1] = 0;
	}

	cameraRange();
}

void cameraManager::updateCamera(RECT& player, float ratioX1, float ratioX2, float ratioY1, float ratioY2)
{
	if (ratioX1 > 0 && ratioX1 < 0.5f)
	{
		if (player.left < _cameraBuffer->getX() + ratioX1 * WINSIZEX)
		{
			_cameraBuffer->setX(player.left - ratioX1 * WINSIZEX);
		}
	}

	if (ratioX2 > 0.5f && ratioX2 < 1.0f)
	{
		if (player.right > _cameraBuffer->getX() + ratioX2 * WINSIZEX)
		{
			_cameraBuffer->setX(player.right - ratioX2 * WINSIZEX);
		}
	}

	if (ratioY1 > 0 && ratioY1 < 0.5f)
	{
		if (player.top < _cameraBuffer->getY() + ratioY1 * WINSIZEY)
		{
			_cameraBuffer->setY(player.top - ratioY1 * WINSIZEY);
		}
	}

	if (ratioY2 > 0.5f && ratioY2 < 1.0f)
	{
		if (player.bottom > _cameraBuffer->getY() + ratioY2 * WINSIZEY)
		{
			_cameraBuffer->setY(player.bottom - ratioY2 * WINSIZEY);
		}
	}
	cameraRange();

	if (ratioX1 != 0)
	{
		x[0] = _cameraBuffer->getX() + ratioX1 * WINSIZEX;
	}
	if (ratioX2 != 0)
	{
		x[1] = _cameraBuffer->getX() + ratioX2 * WINSIZEX;
	}
	if (ratioY1 != 0)
	{
		y[0] = _cameraBuffer->getY() + ratioY1 * WINSIZEY;
	}
	if (ratioY2 != 0)
	{
		y[1] = _cameraBuffer->getY() + ratioY2 * WINSIZEY;
	}
}

