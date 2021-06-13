#include "stdafx.h"
#include "items.h"

//================== C O I N ====================
HRESULT coin::init()
{
	return S_OK;
}

void coin::release()
{
	for (_viCoin = _vCoin.begin(); _viCoin != _vCoin.end(); ++_viCoin)
	{
		SAFE_RELEASE(_viCoin->itemImage);
		SAFE_DELETE(_viCoin->itemImage);
		SAFE_RELEASE(_viCoin->effectImage);
		SAFE_DELETE(_viCoin->effectImage);
	}
	_vCoin.clear();
}

void coin::update()
{
	move();
}

void coin::render()
{
	for (_viCoin = _vCoin.begin(); _viCoin != _vCoin.end(); ++_viCoin)
	{
		//렉트 보여줌
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			Rectangle(getMemDC(), _viCoin->rc);
		}

		//코인이 점프하고 멈춘게 아니라면 코인이미지
		if (!_viCoin->isStop)
		{
			_viCoin->itemImage->frameRender(getMemDC(),
				_viCoin->rc.left,
				_viCoin->rc.top,
				_viCoin->itemImage->getFrameX(), 0);

			_viCoin->count++;

			if (_viCoin->count % 5 == 0)
			{
				_viCoin->itemImage->setFrameX(_viCoin->itemImage->getFrameX() + 1);

				if (_viCoin->itemImage->getFrameX() >= _viCoin->itemImage->getMaxFrameX())
				{
					_viCoin->itemImage->setFrameX(0);
				}
				_viCoin->count = 0;
			}
		}
		else //멈췄으면 이펙트 이미지 실행
		{
			_viCoin->effectImage->frameRender(getMemDC(),
				_viCoin->rc.left,
				_viCoin->rc.top,
				_viCoin->effectImage->getFrameX(), 0);

			_viCoin->count++;

			if (_viCoin->count % 5 == 0)
			{
				_viCoin->effectImage->setFrameX(_viCoin->effectImage->getFrameX() + 1);

				if (_viCoin->effectImage->getFrameX() >= _viCoin->effectImage->getMaxFrameX())
				{
					_viCoin->effectImage->setFrameX(_viCoin->effectImage->getMaxFrameX());
				}
				_viCoin->count = 0;
			}
		}
	}
}

void coin::fire(float x, float y)
{
	tagCoin item;
	ZeroMemory(&item, sizeof(tagCoin));
	item.itemImage = new image;
	item.itemImage->init("img/block/coin.bmp", 168, 48, 4, 1, true, RGB(255, 0, 255));
	item.effectImage = new image;
	item.effectImage->init("img/block/coin_effect.bmp", 144, 48, 3, 1, true, RGB(0, 0, 0));
	item.jumpPower = 8.0f;
	item.x = item.fireX = x;
	item.y = item.fireY = y;

	item.rc = RectMakeCenter(item.x, item.y, item.itemImage->getFrameWidth(), item.itemImage->getFrameHeight());

	_vCoin.push_back(item);
}

void coin::move()
{
	for (_viCoin = _vCoin.begin(); _viCoin != _vCoin.end();)
	{
		if (!_viCoin->isStop)
		{
			//코인 점프
			_viCoin->y -= _viCoin->jumpPower;
			_viCoin->jumpPower -= GRAVITY;

		}
		_viCoin->rc = RectMakeCenter(_viCoin->x, _viCoin->y, _viCoin->itemImage->getFrameWidth(), _viCoin->itemImage->getFrameHeight());

		//코인이 점프하다 어느정도 위치까지 내려오면 멈춤
		if (_viCoin->fireY - _viCoin->y < 100 && _viCoin->jumpPower < 0)
		{
			_viCoin->y = _viCoin->fireY - 100;
			_viCoin->jumpPower = 0;
			_viCoin->isStop = true;
		}

		//이펙트가 한번 실행되고 나면 삭제
		if (_viCoin->effectImage->getFrameX() >= _viCoin->effectImage->getMaxFrameX())
		{
			SAFE_RELEASE(_viCoin->itemImage);
			SAFE_DELETE(_viCoin->itemImage);
			SAFE_RELEASE(_viCoin->effectImage);
			SAFE_DELETE(_viCoin->effectImage);
			_viCoin = _vCoin.erase(_viCoin);
		}
		else ++_viCoin;
	}
}

//===============================================

//============== M U S H R O O M ================
HRESULT mushroom::init()
{
	return S_OK;
}

void mushroom::release()
{

}

void mushroom::update()
{
	move();
}

void mushroom::render()
{
	for (_viMushroom = _vMushroom.begin(); _viMushroom != _vMushroom.end(); ++_viMushroom)
	{
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			char str[128];
			sprintf_s(str, "땅? %d 상태? %d", _viMushroom->isOnGround, _viMushroom->state);
			TextOut(getMemDC(), _viMushroom->rc.left, _viMushroom->rc.top - 20, str, strlen(str));
			Rectangle(getMemDC(), _viMushroom->rc);
		}
		_viMushroom->itemImage->render(getMemDC(), _viMushroom->rc.left, _viMushroom->rc.top);
	}
}

void mushroom::fire(float x, float y, bool isRight)
{
	//버섯 생성 및 vector에 담음
	tagItem item;
	ZeroMemory(&item, sizeof(tagItem));
	item.itemImage = IMAGEMANAGER->findImage("mushroom");
	item.x = item.fireX = x;
	item.y = item.fireY = y;
	item.isOnGround = false;
	item.state = ITEM_UP;
	item.fallSpeed = 4.0f;
	item.isRight = isRight;
	item.rc = RectMakeCenter(item.x, item.y, item.itemImage->getWidth(), item.itemImage->getHeight());

	_vMushroom.push_back(item);
}

void mushroom::move()
{
	for (_viMushroom = _vMushroom.begin(); _viMushroom != _vMushroom.end();)
	{

		switch (_viMushroom->state)
		{
		case ITEM_UP:
			_viMushroom->y -= 2;
			break;
		case ITEM_LEFT:
			_viMushroom->x -= ITEMSPEED;
			break;
		case ITEM_RIGHT:
			_viMushroom->x += ITEMSPEED;
			break;
		default:
			break;
		}

		if (_viMushroom->fireY - _viMushroom->y > _viMushroom->itemImage->getHeight() && _viMushroom->state == ITEM_UP)
		{
			_viMushroom->y = _viMushroom->fireY - _viMushroom->itemImage->getHeight();
			if (_viMushroom->isRight)
			{
				_viMushroom->state = ITEM_RIGHT;
			}
			else
			{
				_viMushroom->state = ITEM_LEFT;
			}
		}
		if (!_viMushroom->isOnGround && _viMushroom->state != ITEM_UP) //공중이라면
		{
			_viMushroom->y += _viMushroom->fallSpeed;
			_viMushroom->fallSpeed += GRAVITY;
		}
		else if (_viMushroom->isOnGround)
		{
			_viMushroom->fallSpeed = 4.0f;
		}

		_viMushroom->rc = RectMakeCenter(_viMushroom->x, _viMushroom->y, _viMushroom->itemImage->getWidth(), _viMushroom->itemImage->getHeight());


		//맵 밖으로 나가면 삭제
		if (_viMushroom->y > BACKGROUNDY || _viMushroom->x <0 || _viMushroom->x>BACKGROUNDX)
		{
			//삭제
			SAFE_RELEASE(_viMushroom->itemImage);
			SAFE_DELETE(_viMushroom->itemImage);
			_viMushroom = _vMushroom.erase(_viMushroom);
		}
		else ++_viMushroom;

		//나온지 몇초 지나면 삭제되게도 구현필요
	}
}

void mushroom::removeMushroom(int arrNum)
{
	//삭제
	_vMushroom.erase(_vMushroom.begin() + arrNum);
}

//===============================================

HRESULT leaf::init()
{
	return S_OK;
}

void leaf::release()
{

}

void leaf::update()
{
	move();
}

void leaf::render()
{
	for (_viLeaf = _vLeaf.begin(); _viLeaf != _vLeaf.end(); ++_viLeaf)
	{
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			char str[128];
			sprintf_s(str, "땅? %d 상태? %d", _viLeaf->isOnGround, _viLeaf->state);
			TextOut(getMemDC(), _viLeaf->rc.left, _viLeaf->rc.top - 20, str, strlen(str));
			Rectangle(getMemDC(), _viLeaf->rc);
		}
		_viLeaf->itemImage->frameRender(getMemDC(), _viLeaf->rc.left, _viLeaf->rc.top, 0, _viLeaf->currentFrameY);
	}
}

void leaf::fire(float x, float y, bool isRight)
{
	//나뭇잎 생성 및 vector에 담음
	tagItem item;
	ZeroMemory(&item, sizeof(tagItem));
	item.itemImage = IMAGEMANAGER->findImage("leaf");
	item.x = item.fireX = x;
	item.y = item.fireY = y;
	item.isOnGround = false;
	item.state = ITEM_UP;
	item.fallSpeed = 5.0f;
	item.angle = PI/2;
	item.isRight = isRight;
	if (isRight)
	{
		item.currentFrameY = 1;
	}
	else
	{
		item.currentFrameY = 0;
	}
	item.rc = RectMakeCenter(item.x, item.y, item.itemImage->getWidth(), item.itemImage->getHeight());

	_vLeaf.push_back(item);
}

void leaf::move()
{
	for (_viLeaf = _vLeaf.begin(); _viLeaf != _vLeaf.end();)
	{
		switch (_viLeaf->state)
		{
		case ITEM_UP:
			_viLeaf->y -=10;
			break;
		case ITEM_LEFT:
			_viLeaf->angle += 0.1f;
			_viLeaf->x += cosf(_viLeaf->angle)*_viLeaf->fallSpeed;
			_viLeaf->y -= -sinf(_viLeaf->angle) * _viLeaf->fallSpeed;
			break;
		case ITEM_RIGHT:
			_viLeaf->angle -= 0.1f;
			_viLeaf->x += cosf(_viLeaf->angle)*_viLeaf->fallSpeed;
			_viLeaf->y -= -sinf(_viLeaf->angle) * _viLeaf->fallSpeed;
			break;
		}

		if (_viLeaf->y < _viLeaf->fireY - (_viLeaf->itemImage->getHeight() * 1.5f))
		{
			if (_viLeaf->isRight)
			{
				_viLeaf->currentFrameY = 1;
				_viLeaf->state = ITEM_RIGHT;
			}
			else
			{
				_viLeaf->currentFrameY = 0;
				_viLeaf->state = ITEM_LEFT;
			}
		}

		if (_viLeaf->isRight)
		{
			if (_viLeaf->x < _viLeaf->fireX)
			{
				_viLeaf->x = _viLeaf->fireX;
				_viLeaf->currentFrameY = 1;
				_viLeaf->state = ITEM_RIGHT;
			}
			else if (_viLeaf->x > _viLeaf->fireX + _viLeaf->itemImage->getWidth() * 1.7f)
			{
				_viLeaf->x = _viLeaf->fireX + _viLeaf->itemImage->getWidth() * 1.7f;
				_viLeaf->currentFrameY = 0;
				_viLeaf->state = ITEM_LEFT;

			}
		}
		else
		{
			if (_viLeaf->x > _viLeaf->fireX)
			{
				_viLeaf->x = _viLeaf->fireX;
				_viLeaf->currentFrameY = 0;
				_viLeaf->state = ITEM_LEFT;
			}
			else if (_viLeaf->x < _viLeaf->fireX - _viLeaf->itemImage->getWidth())
			{
				_viLeaf->x = _viLeaf->fireX - _viLeaf->itemImage->getWidth();
				_viLeaf->currentFrameY = 1;
				_viLeaf->state = ITEM_RIGHT;

			}
		}

		_viLeaf->rc = RectMakeCenter(_viLeaf->x, _viLeaf->y, _viLeaf->itemImage->getWidth(), _viLeaf->itemImage->getHeight());

		if (_viLeaf->rc.top > BACKGROUNDY)
		{
			_viLeaf = _vLeaf.erase(_viLeaf);
		}
		else ++_viLeaf;
	}
}

void leaf::removeLeaf(int arrNum)
{
	_vLeaf.erase(_vLeaf.begin() + arrNum);
}
