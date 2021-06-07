#include "stdafx.h"
#include "playGround.h"

//초기화
HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("map", "img/map.bmp", BACKGROUNDX, BACKGROUNDY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("qBlock", "img/question_block.bmp", 192, 48, 4, 1, true, RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("gBlock", "img/golden_block.bmp", 192, 48, 4, 1, true, RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("coin", "img/coin.bmp", 168, 48, 4, 1, true, RGB(255, 0, 255));

	map = IMAGEMANAGER->findImage("map");

	_player.x = BACKGROUNDX/2;
	_player.y = BACKGROUNDY - 72;

	_player.rc = RectMakeCenter(_player.x, _player.y, 48, 48);

	CAMERAMANAGER->setCameraCenter(_player.x, _player.y);

	_mManager = new mapManager;
	_mManager->init();

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

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player.x -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player.x += 5;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_player.y -= 5;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_player.y += 5;
	}
	_player.rc = RectMakeCenter(_player.x, _player.y, 48, 48);
	_mManager->update();
	CAMERAMANAGER->updateCamera(_player.rc, 0.42f, 0.57f, 0.3f, 0.7f);
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, BACKGROUNDX, BACKGROUNDY, WHITENESS);
	//==================================================

	map->render(getMemDC(), 0, 0);
	Rectangle(getMemDC(), _player.rc);

	_mManager->render();
	//==================================================
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
}
