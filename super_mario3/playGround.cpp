#include "stdafx.h"
#include "playGround.h"

//�ʱ�ȭ
HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("map", "img/map.bmp", BACKGROUNDX, BACKGROUNDY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background", "img/background.bmp", BACKGROUNDX, BACKGROUNDY, true, RGB(255, 0, 255));

	_resetCount = 0;

	//�÷��̾� �ʱ�ȭ
	_player = new player;
	_player->init();

	CAMERAMANAGER->setCameraCenter(_player->getX(), _player->getY());

	//�� �ʱ�ȭ
	_mManager = new mapManager;
	_mManager->init();

	//��� �ʱ�ȭ
	_bManager = new blockManager;
	_bManager->init();

	//���ʹ� �ʱ�ȭ
	_eManager = new enemyManager;
	_eManager->init();

	_player->setMapManagerMemeoryAddressLink(_mManager);
	_player->setBlockManagerMemoryAddressLink(_bManager);
	
	_bManager->setMapManagerMemeoryAddressLink(_mManager);

	_eManager->setPlayerMemeoryAddressLink(_player);
	return S_OK;
}

//�޸� ����
void playGround::release()
{
	gameNode::release();
}


void playGround::update()
{
	gameNode::update();

	if (_player->getRect().top >= BACKGROUNDY)
	{
		_resetCount++;
		if (_resetCount % 50 == 0)
		{
			this->init();
		}
	}

	_eManager->update();
	_mManager->update();
	_bManager->update();
	_player->update();
	
	CAMERAMANAGER->updateCamera(_player->getRect(), 0.42f, 0.57f, 0.3f, 0.7f);
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, BACKGROUNDX, BACKGROUNDY, WHITENESS);
	//==================================================

	IMAGEMANAGER->findImage("background")->render(getMemDC(), 0, 0);

	IMAGEMANAGER->findImage("map")->render(getMemDC(), 0, 0);
	
	_eManager->render();
	_bManager->render();
	_mManager->render();
	_player->render();
	//==================================================
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
}
