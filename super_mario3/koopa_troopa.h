#pragma once
#include "enemy.h"
class koopa_troopa : public enemy
{
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void move();
	virtual void draw();
};

