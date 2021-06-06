#pragma once
#include "gameNode.h"
#include "mapManager.h"

struct tagPlayer
{
	RECT rc;
	float x, y;
};
class playGround : public gameNode
{
private:
	image* map;
	tagPlayer _player;
	mapManager* _mManager;

	//¶¥
	RECT _ground[6];

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

