#pragma once
#include "enemy.h"
class piranha_plant : public enemy
{
private:
	RECT _body;
	image* _bodyImage;
	int _fireCount;
	int _outCount;

public:
	virtual HRESULT init(EnemyState es, POINT position);
	virtual void move();
	virtual void draw();

	bool bulletCountFire();


};

