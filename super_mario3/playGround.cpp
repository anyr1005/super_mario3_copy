#include "stdafx.h"
#include "playGround.h"

//초기화
HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("map", "img/map.bmp", BACKGROUNDX, BACKGROUNDY, true, RGB(255, 0, 255), FALSE);
	IMAGEMANAGER->addImage("background", "img/background.bmp", BACKGROUNDX, BACKGROUNDY, true, RGB(255, 0, 255), FALSE);
	IMAGEMANAGER->addImage("title", "img/title.bmp", 768, 576, true, RGB(255, 0, 255), FALSE);
	IMAGEMANAGER->addFrameImage("title_number", "img/title number.bmp", 576, 144, 6, 1, true, RGB(255, 0, 255), FALSE);
	
	_resetCount = 0;

	//플레이어 초기화
	_player = new player;
	_player->init();

	CAMERAMANAGER->setCamera(_player->getX(), _player->getY());

	CAMERAMANAGER->updateCamera(_player->getRect(), 0.42f, 0.57f, 0, 0);

	//맵 초기화
	_mManager = new mapManager;
	_mManager->init();

	//블록 초기화
	_bManager = new blockManager;
	_bManager->init();

	//에너미 초기화
	_eManager = new enemyManager;
	_eManager->init();

	_player->setMapManagerMemeoryAddressLink(_mManager);
	_player->setBlockManagerMemoryAddressLink(_bManager);
	
	_bManager->setMapManagerMemeoryAddressLink(_mManager);

	_eManager->setPlayerMemeoryAddressLink(_player);
	_eManager->setMapManagerMemoryAddressLink(_mManager);
	_eManager->setBlockManagerMemoryAddressLink(_bManager);
	
	_count = 0;

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

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (!_isStart) _isStart = true;
	}

	if (_isStart)
	{
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

		if (_player->getPlayerState()->getStateName() == PLAYER_FLY || CAMERAMANAGER->getCameraBOTTOM() < BACKGROUNDY )
		{
			CAMERAMANAGER->updateCamera(_player->getRect(), 0.42f, 0.57f, 0.3f, 0.75f);
		}
		else
		{
			CAMERAMANAGER->updateCamera(_player->getRect(), 0.42f, 0.57f, 0, 0);
		}
	}
	else
	{
		_count++;
		if (_count % 10 == 0)
		{
			IMAGEMANAGER->findImage("title_number")->setFrameX(IMAGEMANAGER->findImage("title_number")->getFrameX() + 1);
			if (IMAGEMANAGER->findImage("title_number")->getFrameX() >= IMAGEMANAGER->findImage("title_number")->getMaxFrameX())
			{
				IMAGEMANAGER->findImage("title_number")->setFrameX(0);
			}
		}
	}
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, BACKGROUNDX, BACKGROUNDY, WHITENESS);
	//==================================================

	if (!_isStart)
	{
		IMAGEMANAGER->findImage("title")->render(getMemDC(), _player->getX()-100, _player->getY() - 506);
		IMAGEMANAGER->findImage("title_number")->frameRender(getMemDC(), _player->getX() + 236, _player->getY() - 506 + 288, IMAGEMANAGER->findImage("title_number")->getFrameX(), 0);
	}
	else
	{
		IMAGEMANAGER->findImage("background")->render(getMemDC(), 0, 0);

		IMAGEMANAGER->findImage("map")->render(getMemDC(), 0, 0);
		SetBkMode(getMemDC(), TRANSPARENT);
		_bManager->render();
		_eManager->render();
		_mManager->render();
		_player->render();
	}
	
	//==================================================
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
}
