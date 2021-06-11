#include "stdafx.h"
#include "playGround.h"

//초기화
HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("map", "img/map.bmp", BACKGROUNDX, BACKGROUNDY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background", "img/background.bmp", BACKGROUNDX, BACKGROUNDY, true, RGB(255, 0, 255));

	map = IMAGEMANAGER->findImage("map");

	_player = new player;
	_player->init();

	CAMERAMANAGER->setCameraCenter(_player->getX(), _player->getY());

	_mManager = new mapManager;
	_mManager->init();

	_bManager = new blockManager;
	_bManager->init();

	_eManager = new enemyManager;
	_eManager->init();

	_player->setMapManagerMemeoryAddressLink(_mManager);
	_player->setBlockManagerMemoryAddressLink(_bManager);
	
	_bManager->setMapManagerMemeoryAddressLink(_mManager);

	_eManager->setPlayerMemeoryAddressLink(_player);
	return S_OK;
}

//메모리 해제
void playGround::release()
{
	gameNode::release();
}


void playGround::update()
{
	gameNode::update();

	
	_mManager->update();
	_bManager->update();
	_player->update();
	_eManager->update();
	CAMERAMANAGER->updateCamera(_player->getRect(), 0.42f, 0.57f, 0.3f, 0.7f);
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, BACKGROUNDX, BACKGROUNDY, WHITENESS);
	//==================================================

	IMAGEMANAGER->findImage("background")->render(getMemDC(), 0, 0);

	IMAGEMANAGER->findImage("map")->render(getMemDC(), 0, 0);
	//map->render(getMemDC(), 0, 0);

	_eManager->render();
	_bManager->render();
	_mManager->render();
	_player->render();
	//==================================================
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
}
