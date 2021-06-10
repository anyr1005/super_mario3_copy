#include "stdafx.h"
#include "enemyManager.h"
#include "goomba.h"
#include "koopa_troopa.h"

HRESULT enemyManager::init()
{
	//±À¹Ù ÀÌ¹ÌÁö
	IMAGEMANAGER->addFrameImage("goomba_walk", "img/goomba/goomba_walk.bmp", 96, 48, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("goomba_wing", "img/goomba/goomba_wing.bmp", 240, 72, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("goomba_crush", "img/goomba/goomba_crush.bmp", 48, 27, true, RGB(255, 0, 255));
	
	//¾û±Ý¾û±Ý ÀÌ¹ÌÁö
	//ÃÊ·Ï»ö
	IMAGEMANAGER->addFrameImage("green_walk", "img/koopa_troopa/green_walk.bmp", 96, 162, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("green_wing", "img/koopa_troopa/green_wing.bmp", 192, 168, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("green_shell", "img/koopa_troopa/green_shell.bmp", 192, 48, 4, 1, true, RGB(255, 0, 255));
	//»¡°£»ö
	IMAGEMANAGER->addFrameImage("red_walk", "img/koopa_troopa/red_walk.bmp", 96, 162, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_wing", "img/koopa_troopa/red_wing.bmp", 192, 168, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_shell", "img/koopa_troopa/red_shell.bmp", 192, 48, 4, 1, true, RGB(255, 0, 255));

	//»µ²ûÇÃ¶ó¿ö ÀÌ¹ÌÁö

	setGoomba();
	setKTroopa();
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
	for (_viKTroopa = _vKTroopa.begin(); _viKTroopa != _vKTroopa.end(); ++_viKTroopa)
	{
		(*_viKTroopa)->update();
	}
}

void enemyManager::render()
{
	for (_viGoomba = _vGoomba.begin(); _viGoomba != _vGoomba.end(); ++_viGoomba)
	{
		(*_viGoomba)->render();
	}
	for (_viKTroopa = _vKTroopa.begin(); _viKTroopa != _vKTroopa.end(); ++_viKTroopa)
	{
		(*_viKTroopa)->render();
	}
}

void enemyManager::setGoomba()
{
	goomba* g;
	g = new goomba;
	g->init(LEFT_JUMP , PointMake(700, 1226));
	_vGoomba.push_back(g);

	g = new goomba;
	g->init(RIGHT_WALK, PointMake(700, 1226));
	_vGoomba.push_back(g);
}

void enemyManager::setKTroopa()
{
	koopa_troopa* k;
	k = new koopa_troopa;
	k->init(LEFT_JUMP, PointMake(700, 1226));
	_vKTroopa.push_back(k);

	k = new koopa_troopa;
	k->init(RIGHT_WALK, PointMake(500, 1226));
	_vKTroopa.push_back(k);
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
