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
		//��Ʈ ������
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			Rectangle(getMemDC(), _viCoin->rc);
		}

		//������ �����ϰ� ����� �ƴ϶�� �����̹���
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
		else //�������� ����Ʈ �̹��� ����
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
			//���� ����
			_viCoin->y -= _viCoin->jumpPower;
			_viCoin->jumpPower -= GRAVITY;

		}
		_viCoin->rc = RectMakeCenter(_viCoin->x, _viCoin->y, _viCoin->itemImage->getFrameWidth(), _viCoin->itemImage->getFrameHeight());
	
		//������ �����ϴ� ������� ��ġ���� �������� ����
		if (_viCoin->fireY - _viCoin->y < 100 && _viCoin->jumpPower < 0)
		{
			_viCoin->y = _viCoin->fireY - 100;
			_viCoin->jumpPower = 0;
			_viCoin->isStop = true;
		}
	
		//����Ʈ�� �ѹ� ����ǰ� ���� ����
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
	for (_viMushroom = _vMushroom.begin(); _viMushroom != _vMushroom.end(); ++_viMushroom)
	{
		SAFE_RELEASE(_viMushroom->itemImage);
		SAFE_DELETE(_viMushroom->itemImage);
	}
	_vMushroom.clear();
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
			sprintf_s(str, "��? %d ����? %d", _viMushroom->isOnGround, _viMushroom->state);
			TextOut(getMemDC(), _viMushroom->rc.left, _viMushroom->rc.top - 20, str, strlen(str));
			Rectangle(getMemDC(), _viMushroom->rc);
		}
		_viMushroom->itemImage->render(getMemDC(), _viMushroom->rc.left, _viMushroom->rc.top);
	}
}

void mushroom::fire(float x, float y, bool isRight)
{
	//���� ���� �� vector�� ����
	tagItem item;
	ZeroMemory(&item, sizeof(tagItem));
	item.itemImage = new image;
	item.itemImage->init("img/item/mushroom.bmp", 48, 48, true, RGB(255, 0, 255));
	item.x = item.fireX = x;
	item.y = item.fireY = y;
	item.isOnGround = false;
	item.state = ITEM_UP;
	item.fallPower = 4.0f;
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
			_viMushroom->state = ITEM_RIGHT;
		}
		if (!_viMushroom->isOnGround && _viMushroom->state != ITEM_UP) //�����̶��
		{
			_viMushroom->y += _viMushroom->fallPower;
			_viMushroom->fallPower += GRAVITY;
		}
		else if(_viMushroom->isOnGround)
		{
			_viMushroom->fallPower = 4.0f;
		}
		
		_viMushroom->rc = RectMakeCenter(_viMushroom->x, _viMushroom->y, _viMushroom->itemImage->getWidth(), _viMushroom->itemImage->getHeight());

		
		//�� ������ ������ ����
		if (_viMushroom->y > BACKGROUNDY || _viMushroom->x <0 || _viMushroom->x>BACKGROUNDX)
		{
			//����
			SAFE_RELEASE(_viMushroom->itemImage);
			SAFE_DELETE(_viMushroom->itemImage);
			_viMushroom = _vMushroom.erase(_viMushroom);
		}
		else ++_viMushroom;
		
		//������ ���� ������ �����ǰԵ� �����ʿ�
	}
}

void mushroom::removeMushroom(int arrNum)
{
	//����
	SAFE_RELEASE(_vMushroom[arrNum].itemImage);
	SAFE_DELETE(_vMushroom[arrNum].itemImage);
	_vMushroom.erase(_vMushroom.begin() + arrNum );
}

//===============================================