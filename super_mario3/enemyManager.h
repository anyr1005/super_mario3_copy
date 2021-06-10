#pragma once
#include "gameNode.h"
#include "koopa_troopa.h"
#include "goomba.h"
#include <vector>

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;

private:
	vEnemy _vGoomba;
	viEnemy _viGoomba;
	vEnemy _vKTroopa;
	viEnemy _viKTroopa;
	vEnemy _vFlower;
	viEnemy _viFlower;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setGoomba();
	void setKTroopa();
	void setFlower();

	void removeGoomba(int arrNum);
	void removeKTroopa(int arrNum);
	void removeFlower(int arrNum);

};

