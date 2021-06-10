#pragma once
#include "enemy.h"
class koopa_troopa : public enemy
{
private : 
	bool _isShell;
public:
	virtual HRESULT init(EnemyState es, POINT position);
	virtual void move();
	virtual void draw();
};

