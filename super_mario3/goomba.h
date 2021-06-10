#pragma once
#include "enemy.h"

class goomba : public enemy
{
private:
	int _jumpCount;
	bool _isBigJump;

	RECT _collisonRange;
public:
	virtual HRESULT init(EnemyState es, POINT position);
	virtual void move();
	virtual void draw();
	
	RECT getCollisonRange() { return _collisonRange; }
};

