#pragma once
#include "enemy.h"

class goomba : public enemy
{
private:
	int _jumpCount;
	bool _isBigJump;

	int _deadCount;

	EnemyState _firstState; //초기 상태

public:
	virtual HRESULT init(EnemyState es, POINT position);
	virtual void move();
	virtual void draw();
	
	
};

