#include "stdafx.h"
#include "enemyManager.h"
#include "goomba.h"
#include "koopa_troopa.h"
#include "playerJump.h"
#include "piranha_plant.h"

HRESULT enemyManager::init()
{
	//굼바 이미지
	IMAGEMANAGER->addFrameImage("goomba_walk", "img/goomba/goomba_walk.bmp", 96, 48, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("goomba_wing", "img/goomba/goomba_wing.bmp", 240, 72, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("goomba_crush", "img/goomba/goomba_crush.bmp", 48, 27, 1, 1, true, RGB(255, 0, 255));

	//엉금엉금 이미지
	//초록색
	IMAGEMANAGER->addFrameImage("green_walk", "img/koopa_troopa/green_walk.bmp", 96, 162, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("green_wing", "img/koopa_troopa/green_wing.bmp", 192, 168, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("green_shell", "img/koopa_troopa/green_shell.bmp", 192, 48, 4, 1, true, RGB(255, 0, 255));
	//빨간색
	IMAGEMANAGER->addFrameImage("red_walk", "img/koopa_troopa/red_walk.bmp", 96, 162, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_wing", "img/koopa_troopa/red_wing.bmp", 192, 168, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_shell", "img/koopa_troopa/red_shell.bmp", 192, 48, 4, 1, true, RGB(255, 0, 255));

	//뻐끔플라워 이미지
	IMAGEMANAGER->addImage("fire_red_left_down", "img/piranha_plant/fire_red_left_down.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fire_red_left_up", "img/piranha_plant/fire_red_left_up.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fire_red_right_up", "img/piranha_plant/fire_red_right_up.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fire_red_right_down", "img/piranha_plant/fire_red_right_down.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("long_leaf_green", "img/piranha_plant/leaf_long_green.bmp", 48, 48, true, RGB(255, 0, 255));

	setGoomba();
	setKTroopa();
	setFlower();

	_bullet = new bullet;
	_bullet->init();

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
	for (_viFlower = _vFlower.begin(); _viFlower != _vFlower.end(); ++_viFlower)
	{
		(*_viFlower)->update();
	}
	goombaCollison();
	troopaCollison();
	flowerCollison();
	flowerBulletFire();
	flowerMoveHead();
	_bullet->update();
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
	for (_viFlower = _vFlower.begin(); _viFlower != _vFlower.end(); ++_viFlower)
	{
		(*_viFlower)->render();
	}
	_bullet->render();
}

void enemyManager::setGoomba()
{
	goomba* g;
	g = new goomba;
	g->init(LEFT_JUMP, PointMake(700, 1226));
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
	piranha_plant* p;
	p = new piranha_plant;
	p->init(IDLE, PointMake(1104, BACKGROUNDY - 168));
	_vFlower.push_back(p);

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

void enemyManager::goombaCollison()
{
	for (_viGoomba = _vGoomba.begin(); _viGoomba != _vGoomba.end(); ++_viGoomba)
	{
		if ((*_viGoomba)->getState() == DIE) continue;

		RECT temp;
		RECT goomba = (*_viGoomba)->getCollisonRange();
		if (IntersectRect(&temp, &goomba, &_player->getRect()))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			if (width > height)
			{
				//player가 위에서 충돌
				if (_player->getY() < (*_viGoomba)->getY())
				{
					EnemyState es = (*_viGoomba)->getState();
					if (es == LEFT_JUMP)
					{
						es = LEFT_WALK;
					}
					else if (es == RIGHT_JUMP)
					{
						es = RIGHT_WALK;
					}
					else if (es == LEFT_WALK || es == RIGHT_WALK)
					{
						es = DIE;
					}
					(*_viGoomba)->setState(es);
					(*_viGoomba)->setY((*_viGoomba)->getY() + 10.5f);
					_player->setY(_player->getY() - height);
					_player->setPlayerState(new playerJump);
					_player->getPlayerState()->enter(_player);
					break;
				}
			}

		}
	}
}

void enemyManager::troopaCollison()
{
	for (_viKTroopa = _vKTroopa.begin(); _viKTroopa != _vKTroopa.end(); ++_viKTroopa)
	{
		RECT temp;
		RECT troopa = (*_viKTroopa)->getCollisonRange();
		if (IntersectRect(&temp, &troopa, &_player->getRect()))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			EnemyState es = (*_viKTroopa)->getState();
			if (width > height)
			{
				//player가 위에서 충돌
				if (_player->getY() < (*_viKTroopa)->getY())
				{
					//등껍질 상태가 아니면
					if (!(*_viKTroopa)->getIsShell())
					{
						if (es == LEFT_JUMP)
						{
							es = LEFT_WALK;
							_player->setY(_player->getY() - height);
						}
						else if (es == RIGHT_JUMP)
						{
							es = RIGHT_WALK;
							_player->setY(_player->getY() - height);
						}
						else if (es == LEFT_WALK || es == RIGHT_WALK)
						{
							es = IDLE;
							(*_viKTroopa)->setIsShell(true);
							//등껍질이 됨에 따라 충돌 렉트가 커지므로 충돌이 다시 되지 않게 27을 더 빼줌
							_player->setY(_player->getY() - height - 27);
						}
					}
					//등껍질 상태이면
					else
					{
						if ((*_viKTroopa)->getState() == IDLE)
						{
							if (_player->getX() < (*_viKTroopa)->getX())
							{
								es = RIGHT_WALK;
							}
							else
							{
								es = LEFT_WALK;
							}
						}
						else
						{
							es = IDLE;
						}
					}
					_player->setY(_player->getY() - height);
					(*_viKTroopa)->setState(es);
					_player->setPlayerState(new playerJump);
					_player->getPlayerState()->enter(_player);
					break;
				}
				//아래에서 충돌
			}
			else
			{
				//왼쪽에서 충돌
				if (_player->getX() < (*_viKTroopa)->getX())
				{
					if ((*_viKTroopa)->getIsShell())
					{
						//멈춰있으면 등껍질 움직이게함
						if ((*_viKTroopa)->getState() == IDLE)
						{
							es = RIGHT_WALK;
							_player->setX(_player->getX() - width);
						}
						else //움직이는 중에 부딪혔다면 player 죽음
						{

						}
					}
					(*_viKTroopa)->setState(es);
					break;
				}
				else
				{
					if ((*_viKTroopa)->getIsShell())
					{
						//멈춰있으면 등껍질 움직이게함
						if ((*_viKTroopa)->getState() == IDLE)
						{
							es = LEFT_WALK;
							_player->setX(_player->getX() + width);
						}
						else //움직이는 중에 부딪혔다면 player 죽음
						{

						}
					}
					(*_viKTroopa)->setState(es);
					break;
				}
				
			}
		}
	}
}

void enemyManager::flowerCollison()
{
	for (_viFlower = _vFlower.begin(); _viFlower != _vFlower.end(); ++_viFlower)
	{
		RECT flowerRangeRect = (*_viFlower)->getCollisonRange();
		RECT playerRect = _player->getRect();

		if (playerRect.left >= flowerRangeRect.left && playerRect.right <= flowerRangeRect.right
			&&playerRect.top >= flowerRangeRect.top && playerRect.bottom <= flowerRangeRect.bottom)
		{
			(*_viFlower)->setIsVisible(false);

		}
		else
		{
			(*_viFlower)->setIsVisible(true);
		}
	}

	
}

void enemyManager::flowerBulletFire()
{
	for (_viFlower = _vFlower.begin(); _viFlower != _vFlower.end(); ++_viFlower)
	{
		if ((*_viFlower)->bulletCountFire())
		{
			if ((*_viFlower)->getIsVisible())
			{
				float angle = getAngle((*_viFlower)->getX(), (*_viFlower)->getY(), _player->getX(), _player->getY());
				_bullet->fire((*_viFlower)->getX(), (*_viFlower)->getY(), angle, 4.0f);
			}
			(*_viFlower)->setState(RIGHT_WALK);
		}
	}
}

void enemyManager::flowerMoveHead()
{

	//플레이어 따라가는 머리 움직임 처리
	for (_viFlower = _vFlower.begin(); _viFlower != _vFlower.end(); ++_viFlower)
	{
		if (_player->getX() < (*_viFlower)->getX())
		{
			if (_player->getY() < (*_viFlower)->getY())
			{
				(*_viFlower)->setImage("fire_red_left_up");
			}
			else
			{
				(*_viFlower)->setImage("fire_red_left_down");
			}
		}
		else
		{
			if (_player->getY() < (*_viFlower)->getY())
			{
				(*_viFlower)->setImage("fire_red_right_up");
			}
			else
			{
				(*_viFlower)->setImage("fire_red_right_down");
			}
		}
	}
}
