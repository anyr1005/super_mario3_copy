#pragma once
#include "enemy.h"

class goomba : public enemy
{
public:
	virtual HRESULT init(POINT position);
	virtual void move();
	virtual void draw();
};

