#pragma once
#include "gameNode.h"
#include "koopa_troopa.h"
#include "goomba.h"
#include "bullet.h"
#include <vector>

#include "player.h"
#include "mapManager.h"
#include "blockManager.h"

class player;
class mapManager;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;

private:
	//±À¹Ù
	vEnemy _vGoomba;
	viEnemy _viGoomba;
	
	//¾û±Ý¾û±Ý
	vEnemy _vKTroopa;
	viEnemy _viKTroopa;
	
	//»µ²ûÇÃ¶ó¿ö
	vEnemy _vFlower;
	viEnemy _viFlower;

	bullet* _bullet;

	//Ãæµ¹ À§ÇÑ ÂüÁ¶
	player* _player;
	mapManager* _mManager;
	blockManager* _bManager;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setGoomba();
	void setKTroopa();
	void setFlower();

	void goombaCollison();
	void troopaCollison();
	void flowerCollison();

	void flowerBulletFire();
	void flowerMoveHead();

	void setPlayerMemeoryAddressLink(player* p) { _player = p; }
	void setMapManagerMemoryAddressLink(mapManager* m) { _mManager = m; }
	void setBlockManagerMemoryAddressLink(blockManager* b) { _bManager = b; }
};

