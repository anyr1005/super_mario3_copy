#pragma once
#include "enemy.h"

class goomba : public enemy
{
public:
	virtual HRESULT init(EnemyState es, POINT position);
	virtual void move();
	virtual void draw();
};

