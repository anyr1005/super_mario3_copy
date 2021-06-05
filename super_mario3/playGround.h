#pragma once
#include "gameNode.h"

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

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

