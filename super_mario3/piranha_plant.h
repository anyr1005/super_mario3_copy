#pragma once
#include "enemy.h"
class piranha_plant : public enemy
{
	virtual HRESULT init(EnemyState es, POINT position);
	virtual void move();
	virtual void draw();
};

