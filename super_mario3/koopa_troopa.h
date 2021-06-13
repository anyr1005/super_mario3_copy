#pragma once
#include "enemy.h"
class koopa_troopa : public enemy
{
private:
	float _rangeX1; //�����̴� ���� left
	float _rangeX2; //�����̴� ���� right
	bool _isHaveRange;

public:
	virtual HRESULT init(EnemyState es, POINT position);
	virtual HRESULT init(EnemyState es, POINT position, float x1, float x2);
	virtual void move();
	virtual void draw();
};

