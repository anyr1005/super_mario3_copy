#pragma once
#include "enemy.h"

class goomba : public enemy
{
private:
	int _jumpCount;
	bool _isBigJump;

public:
	virtual HRESULT init(EnemyState es, POINT position);
	virtual void move();
	virtual void draw();
	
};

