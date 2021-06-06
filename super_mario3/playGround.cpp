#include "stdafx.h"
#include "playGround.h"

//초기화
HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("map", "img/map.bmp", BACKGROUNDX, BACKGROUNDY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("qBlock", "img/question_block.bmp", 192, 48, 4, 1, true, RGB(255,0,255));


	map = IMAGEMANAGER->findImage("map");

	_player.x = 100;
	_player.y = BACKGROUNDY - 72;

	_player.rc = RectMakeCenter(_player.x, _player.y, 48, 48);

	_ground[0] = RectMake(0, BACKGROUNDY - 48, 1872, 48);
	_ground[1] = RectMake(_ground[0].right, BACKGROUNDY - 96, 1392, 96);
	_ground[2] = RectMake(BACKGROUNDX/2 - 720, BACKGROUNDY - 48, 1056, 48);
	_ground[3] = RectMake(BACKGROUNDX/2 + 432, BACKGROUNDY - 48, 240, 48);
	_ground[4] = RectMake(BACKGROUNDX/2 + 816, BACKGROUNDY - 48, 1632, 48);
	_ground[5] = RectMake(BACKGROUNDX - 1680, BACKGROUNDY - 48, 1680, 48);
	CAMERAMANAGER->setCameraCenter(_player.x, _player.y);

	_mManager = new mapManager;
	_mManager->init();
	_mManager->setQuestionBlock();

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
	CAMERAMANAGER->updateCamera(_player.rc, 0.42f, 0.57f, 0, 0);
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, BACKGROUNDX, BACKGROUNDY, WHITENESS);
	//==================================================

	map->render(getMemDC(), 0, 0);
	Rectangle(getMemDC(), _player.rc);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 6; i++)
		{
			Rectangle(getMemDC(), _ground[i]);
		}
	}
	_mManager->render();
	//==================================================
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
}
