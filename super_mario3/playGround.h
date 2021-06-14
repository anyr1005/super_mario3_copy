#pragma once
#include "gameNode.h"
#include "mapManager.h"
#include "blockManager.h"
#include "enemyManager.h"
#include "player.h"

class playGround : public gameNode
{
private:
	image* map;
	player* _player;

	mapManager* _mManager;

	blockManager* _bManager;

	enemyManager* _eManager;

	int _resetCount;

	bool _isStart;

	int _count; //타이틀 용 카운터
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

