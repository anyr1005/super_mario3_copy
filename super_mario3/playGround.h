#pragma once
#include "gameNode.h"
#include "mapManager.h"
#include "blockManager.h"
#include "player.h"

class playGround : public gameNode
{
private:
	image* map;
	player* _player;
	mapManager* _mManager;
	blockManager* _bManager;

	//¶¥
	RECT _ground[6];

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

