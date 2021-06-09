#include "stdafx.h"
#include "items.h"

HRESULT coin::init()
{
	return S_OK;
}

void coin::release()
{
}

void coin::update()
{
	move();
}

void coin::render()
{
	for (_viCoin = _vCoin.begin(); _viCoin != _vCoin.end(); ++_viCoin)
	{
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
	item.jumpPower = 6.0f;
	item.gravity = 0.1f;
	item.x = item.fireX = x;
	item.y = item.fireY = y;

	item.rc = RectMakeCenter(item.x, item.y, item.itemImage->getFrameWidth(), item.itemImage->getFrameWidth());

	_vCoin.push_back(item);
}

void coin::move()
{
	for (_viCoin = _vCoin.begin(); _viCoin != _vCoin.end();)
	{
		//���� ����
		_viCoin->y -= _viCoin->jumpPower;
		_viCoin->jumpPower -= _viCoin->gravity;

		_viCoin->rc = RectMakeCenter(_viCoin->x, _viCoin->y, _viCoin->itemImage->getFrameWidth(), _viCoin->itemImage->getFrameWidth());
	
		//������ �����ϴ� ������� ��ġ���� �������� ����
		if (_viCoin->fireY - _viCoin->y < 120 && _viCoin->jumpPower < 0)
		{
			_viCoin->y = _viCoin->fireY - 120;
			_viCoin->jumpPower = 0;
			_viCoin->gravity = 0;
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
}

void mushroom::fire(float x, float y, bool isRight)
{
	//���� ���� �� vector�� ����
	tagItem item;
	ZeroMemory(&item, sizeof(tagItem));
	item.itemImage = new image;
	item.itemImage->init("img/item/mushroom.bmp", 48, 48, true, RGB(255, 0, 255));
	item.x = x;
	item.y = y;
	item.rc = RectMakeCenter(item.x, item.y, item.itemImage->getFrameWidth(), item.itemImage->getFrameWidth());

	_vMushroom.push_back(item);
}

void mushroom::move()
{
	for (_viMushroom = _vMushroom.begin(); _viMushroom != _vMushroom.end();)
	{
		//������ ��Ͽ��� ������ ��������
		if (_viMushroom->isFired)
		{
			//���������� ������
			if (_viMushroom->isRight)
			{
				_viMushroom->x += 5;
			}
			else //�������� ������
			{
				_viMushroom->x -= 5;
			}
			if (!_viMushroom->isOnGround) //�����̶��
			{
				_viMushroom->y += 4.0f;
			}
		}
		else //�� ������ �ʾ����� �� ���� ����
		{
			_viMushroom->y += 5;
		}
		
		_viMushroom->rc = RectMakeCenter(_viMushroom->x, _viMushroom->y, _viMushroom->itemImage->getFrameWidth(), _viMushroom->itemImage->getFrameWidth());

		//�� ������ ������ ����
		if (_viMushroom->y > BACKGROUNDY || _viMushroom->x <0 || _viMushroom->x>BACKGROUNDX)
		{
			//����
			SAFE_RELEASE(_viMushroom->itemImage);
			SAFE_DELETE(_viMushroom->itemImage);
			_viMushroom = _vMushroom.erase(_viMushroom);
		}
		else ++_viMushroom;
	}
}

void mushroom::removeMushroom(int arrNum)
{
	//����
	SAFE_RELEASE(_vMushroom[arrNum].itemImage);
	SAFE_DELETE(_vMushroom[arrNum].itemImage);
	_vMushroom.erase(_vMushroom.begin() + arrNum );
}
