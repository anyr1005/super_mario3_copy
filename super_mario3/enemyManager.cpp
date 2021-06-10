#include "stdafx.h"
#include "enemyManager.h"
#include "goomba.h"

HRESULT enemyManager::init()
{
	//±À¹Ù ÀÌ¹ÌÁö
	IMAGEMANAGER->addFrameImage("goomba_walk", "img/goomba/goomba_walk.bmp", 96, 48, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("goomba_wing", "img/goomba/goomba_wing.bmp", 240, 72, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("goomba_crush", "img/goomba/goomba_crush.bmp", 48, 27, true, RGB(255, 0, 255));
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
	g->init(LEFT_WALK , PointMake(700, 1226));
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
