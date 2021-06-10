#include "stdafx.h"
#include "enemyManager.h"
#include "goomba.h"

HRESULT enemyManager::init()
{
	setGoomba();
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (_viGoomba = _vGoomba.begin(); _viGoomba != _vGoomba.end(); ++_viGoomba)
	{
		(*_viGoomba)->update();
	}
}

void enemyManager::render()
{
	for (_viGoomba = _vGoomba.begin(); _viGoomba != _vGoomba.end(); ++_viGoomba)
	{
		(*_viGoomba)->render();
	}
}

void enemyManager::setGoomba()
{
	goomba* g;
	g = new goomba;
	g->init(PointMake(700, 1226));
	_vGoomba.push_back(g);
}

void enemyManager::setKTroopa()
{
}

void enemyManager::setFlower()
{
}

void enemyManager::removeGoomba(int arrNum)
{
	
}

void enemyManager::removeKTroopa(int arrNum)
{
}

void enemyManager::removeFlower(int arrNum)
{
}
