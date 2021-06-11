#include "stdafx.h"
#include "enemyManager.h"
#include "goomba.h"
#include "koopa_troopa.h"
#include "piranha_plant.h"
#include "playerJump.h"
#include "playerDie.h"

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
	
	flowerCollison();
	flowerBulletFire();
	flowerMoveHead();

	goombaCollison();
	troopaCollison();
	
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
	g->init(ENEMY_LEFT_JUMP, PointMake(900, 600));
	_vGoomba.push_back(g);

	g = new goomba;
	g->init(ENEMY_RIGHT_WALK, PointMake(700, 1224));
	_vGoomba.push_back(g);

	g = new goomba;
	g->init(ENEMY_LEFT_WALK, PointMake(1500, 600));
	_vGoomba.push_back(g);
}

void enemyManager::setKTroopa()
{
	koopa_troopa* k;
	k = new koopa_troopa;
	k->init(ENEMY_LEFT_JUMP, PointMake(700, 1226));
	_vKTroopa.push_back(k);

	k = new koopa_troopa;
	k->init(ENEMY_RIGHT_WALK, PointMake(1500, 1112));
	_vKTroopa.push_back(k);
}

void enemyManager::setFlower()
{
	piranha_plant* p;
	p = new piranha_plant;
	p->init(ENEMY_IDLE, PointMake(1104, BACKGROUNDY - 168));
	_vFlower.push_back(p);

}

void enemyManager::goombaCollison()
{
	//플레이어와 충돌
	for (_viGoomba = _vGoomba.begin(); _viGoomba != _vGoomba.end(); ++_viGoomba)
	{
		//플레이어가 죽은 상태면 충돌 확인 안함
		if (_player->getPlayerState()->getStateName() == PLAYER_DIE) break;
		//굼바가 죽은 상태면 충돌 확인 안함
		if ((*_viGoomba)->getState() == ENEMY_DIE) continue;

		RECT temp;
		RECT goombaRect = (*_viGoomba)->getCollisonRange();
		
		if (IntersectRect(&temp, &goombaRect, &_player->getRect()))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			if (width > height)
			{
				//player가 위에서 충돌
				if (_player->getY() < (*_viGoomba)->getY())
				{
					EnemyState es = (*_viGoomba)->getState();
					if (es == ENEMY_LEFT_JUMP)
					{
						es = ENEMY_LEFT_WALK;
					}
					else if (es == ENEMY_RIGHT_JUMP)
					{
						es = ENEMY_RIGHT_WALK;
					}
					else if (es == ENEMY_LEFT_WALK || es == ENEMY_RIGHT_WALK)
					{
						es = ENEMY_DIE;
					}
					(*_viGoomba)->setState(es);
					(*_viGoomba)->setY((*_viGoomba)->getY() + 10.5f);
					_player->setY(_player->getY() - height);
					_player->setPlayerState(new playerJump);
					_player->getPlayerState()->enter(_player);
					break;
				}
			}
			else //좌우충돌
			{
				if (_player->getPlayerShape() == BASIC)
				{
					_player->setPlayerState(new playerDie);
					_player->getPlayerState()->enter(_player);
				}
			}
		}

	}

	//거북이 등껍질과 충돌
	for (_viGoomba = _vGoomba.begin(); _viGoomba != _vGoomba.end(); ++_viGoomba)
	{
		//굼바가 죽은 상태면 충돌 확인 안함
		if ((*_viGoomba)->getState() == ENEMY_DIE) continue;

		for (_viKTroopa = _vKTroopa.begin(); _viKTroopa != _vKTroopa.end(); ++_viKTroopa)
		{
			if (!(*_viKTroopa)->getIsShell()) continue;

			RECT temp;
			if (IntersectRect(&temp, &(*_viKTroopa)->getCollisonRange(), &(*_viGoomba)->getCollisonRange()))
			{
				if ((*_viKTroopa)->getState() == ENEMY_LEFT_WALK || (*_viKTroopa)->getState() == ENEMY_RIGHT_WALK)
				{
					if ((*_viGoomba)->getState() == ENEMY_LEFT_WALK || (*_viGoomba)->getState() == ENEMY_RIGHT_WALK)
					{
						(*_viGoomba)->setState(ENEMY_DIE);
					}
					else if ((*_viGoomba)->getState() == ENEMY_LEFT_JUMP)
					{
						(*_viGoomba)->setState(ENEMY_LEFT_WALK);
					}
					else if ((*_viGoomba)->getState() == ENEMY_RIGHT_JUMP)
					{
						(*_viGoomba)->setState(ENEMY_RIGHT_WALK);
					}
				}
			}
		}
	}

	//땅과 충돌
	for (_viGoomba = _vGoomba.begin(); _viGoomba != _vGoomba.end(); ++_viGoomba)
	{
		RECT goombaRect = (*_viGoomba)->getRect();
		(*_viGoomba)->setIsOnGround(false);
		for (int i = 0; i < _mManager->getGround().size(); i++)
		{
			RECT ground = _mManager->getGround()[i];
			RECT temp;
			if (goombaRect.bottom == ground.top && goombaRect.right > ground.left && goombaRect.left < ground.right)
			{
				(*_viGoomba)->setIsOnGround(true);
			}
			if (IntersectRect(&temp, &goombaRect, &ground))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				if (width > height)
				{
					//위에서 충돌
					if ((*_viGoomba)->getY() < (ground.bottom + ground.top) / 2)
					{
						(*_viGoomba)->setY((*_viGoomba)->getY() - height);
						(*_viGoomba)->setIsOnGround(true);
					}
					//땅과는 아래에서 충돌 없음
				}
				else
				{
					if ((*_viGoomba)->getX() < (ground.left + ground.right) / 2)
					{
						(*_viGoomba)->setX((*_viGoomba)->getX() - width);
						if ((*_viGoomba)->getState() == ENEMY_RIGHT_WALK)
						{
							(*_viGoomba)->setState(ENEMY_LEFT_WALK);
						}
						else
						{
							(*_viGoomba)->setState(ENEMY_LEFT_JUMP);
						}
					}
					else
					{
						(*_viGoomba)->setX((*_viGoomba)->getX() + width);
						if ((*_viGoomba)->getState() == ENEMY_LEFT_WALK)
						{
							(*_viGoomba)->setState(ENEMY_RIGHT_WALK);
						}
						else
						{
							(*_viGoomba)->setState(ENEMY_RIGHT_JUMP);
						}
					}
				}
			}
		}
	}

	//object 와 충돌
	for (_viGoomba = _vGoomba.begin(); _viGoomba != _vGoomba.end(); ++_viGoomba)
	{
		RECT goombaRect = (*_viGoomba)->getRect();
		for (int i = 0; i < _mManager->getObject().size(); i++)
		{
			RECT object = _mManager->getObject()[i];
			RECT temp;
			if (goombaRect.bottom == object.top && goombaRect.right > object.left && goombaRect.left < object.right)
			{
				(*_viGoomba)->setIsOnGround(true);
				break;
			}
			if (IntersectRect(&temp, &goombaRect, &object))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				if (width > height)
				{
					//위에서 충돌
					if ((*_viGoomba)->getY() < (object.bottom + object.top) / 2)
					{
						(*_viGoomba)->setY((*_viGoomba)->getY() - height);
						(*_viGoomba)->setIsOnGround(true);
						break;
					}
					//object와는 아래에서 충돌 없음
				}
			}
		}
	}

	//pipe와 충돌
	for (_viGoomba = _vGoomba.begin(); _viGoomba != _vGoomba.end(); ++_viGoomba)
	{
		RECT goombaRect = (*_viGoomba)->getRect();
		for (int i = 0; i < _mManager->getPipe().size(); i++)
		{
			RECT pipe_head = _mManager->getPipe()[i].head;
			RECT pipe_body = _mManager->getPipe()[i].body;
			RECT temp;
			if (goombaRect.bottom == pipe_head.top && goombaRect.right > pipe_head.left && goombaRect.left < pipe_head.right)
			{
				(*_viGoomba)->setIsOnGround(true);
				break;
			}
			if (IntersectRect(&temp, &goombaRect, &pipe_head))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				if (width > height)
				{
					//위에서 충돌
					if ((*_viGoomba)->getY() < (pipe_head.bottom + pipe_head.top) / 2)
					{
						(*_viGoomba)->setY((*_viGoomba)->getY() - height);
						(*_viGoomba)->setIsOnGround(true);
						break;
					}
					//아래에서 충돌
					else
					{
						(*_viGoomba)->setY((*_viGoomba)->getY() + height);
						break;
					}
				}
				//좌우 충돌
				else
				{
					//왼쪽에서 충돌
					if ((*_viGoomba)->getX() < (pipe_head.left + pipe_head.right) / 2)
					{
						(*_viGoomba)->setX((*_viGoomba)->getX() - width);
						if ((*_viGoomba)->getState() == ENEMY_RIGHT_WALK)
						{
							(*_viGoomba)->setState(ENEMY_LEFT_WALK);
						}
						else
						{
							(*_viGoomba)->setState(ENEMY_LEFT_JUMP);
						}
					}
					//오른쪽에서 충돌
					else
					{
						(*_viGoomba)->setX((*_viGoomba)->getX() + width);
						if ((*_viGoomba)->getState() == ENEMY_LEFT_WALK)
						{
							(*_viGoomba)->setState(ENEMY_RIGHT_WALK);
						}
						else
						{
							(*_viGoomba)->setState(ENEMY_RIGHT_JUMP);
						}
					}
				}
			}

			if (IntersectRect(&temp, &goombaRect, &pipe_body))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				//파이프 body는 위아래 충돌 없음
				if (width < height)
				{
					if ((*_viGoomba)->getX() < (pipe_body.left + pipe_body.right) / 2)
					{
						(*_viGoomba)->setX((*_viGoomba)->getX() - width);
						if ((*_viGoomba)->getState() == ENEMY_RIGHT_WALK)
						{
							(*_viGoomba)->setState(ENEMY_LEFT_WALK);
						}
						else
						{
							(*_viGoomba)->setState(ENEMY_LEFT_JUMP);
						}
					}
					else
					{
						(*_viGoomba)->setX((*_viGoomba)->getX() + width);
						if ((*_viGoomba)->getState() == ENEMY_LEFT_WALK)
						{
							(*_viGoomba)->setState(ENEMY_RIGHT_WALK);
						}
						else
						{
							(*_viGoomba)->setState(ENEMY_RIGHT_JUMP);
						}
					}
				}
			}
		}
	}

	//question_block과 충돌
	for (_viGoomba = _vGoomba.begin(); _viGoomba != _vGoomba.end(); ++_viGoomba)
	{
		RECT goombaRect = (*_viGoomba)->getRect();
		for (int i = 0; i < _bManager->getQBlock().size(); i++)
		{
			RECT qBlock = _bManager->getQBlock()[i]->getRect();
			RECT temp;
			if (goombaRect.bottom == qBlock.top && goombaRect.right > qBlock.left && goombaRect.left < qBlock.right)
			{
				(*_viGoomba)->setIsOnGround(true);
				break;
			}
			if (IntersectRect(&temp, &goombaRect, &qBlock))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				if (width > height)
				{
					//위에서 충돌
					if ((*_viGoomba)->getY() < (qBlock.bottom + qBlock.top) / 2)
					{
						(*_viGoomba)->setY((*_viGoomba)->getY() - height);
						(*_viGoomba)->setIsOnGround(true);
						break;
					}
					//아래에서 충돌
					else
					{
						(*_viGoomba)->setY((*_viGoomba)->getY() + height);
						break;
					}
				}
				//좌우 충돌
				else
				{
					//왼쪽에서 충돌
					if ((*_viGoomba)->getX() < (qBlock.left + qBlock.right) / 2)
					{
						(*_viGoomba)->setX((*_viGoomba)->getX() - width);
						if ((*_viGoomba)->getState() == ENEMY_RIGHT_WALK)
						{
							(*_viGoomba)->setState(ENEMY_LEFT_WALK);
						}
						else
						{
							(*_viGoomba)->setState(ENEMY_LEFT_JUMP);
						}
					}
					//오른쪽에서 충돌
					else
					{
						(*_viGoomba)->setX((*_viGoomba)->getX() + width);
						if ((*_viGoomba)->getState() == ENEMY_LEFT_WALK)
						{
							(*_viGoomba)->setState(ENEMY_RIGHT_WALK);
						}
						else
						{
							(*_viGoomba)->setState(ENEMY_RIGHT_JUMP);
						}
					}
				}
			}
		}
	}

	
}

void enemyManager::troopaCollison()
{
	//플레이어와 충돌
	for (_viKTroopa = _vKTroopa.begin(); _viKTroopa != _vKTroopa.end(); ++_viKTroopa)
	{
		if (_player->getPlayerState()->getStateName() == PLAYER_DIE) break;
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
						if (es == ENEMY_LEFT_JUMP)
						{
							es = ENEMY_LEFT_WALK;
							_player->setY(_player->getY() - height);
						}
						else if (es == ENEMY_RIGHT_JUMP)
						{
							es = ENEMY_RIGHT_WALK;
							_player->setY(_player->getY() - height);
						}
						else if (es == ENEMY_LEFT_WALK || es == ENEMY_RIGHT_WALK)
						{
							es = ENEMY_IDLE;
							(*_viKTroopa)->setIsShell(true);
							//등껍질이 됨에 따라 충돌 렉트가 커지므로 충돌이 다시 되지 않게 27을 더 빼줌
							_player->setY(_player->getY() - height - 27);
						}
					}
					//등껍질 상태이면
					else
					{
						if ((*_viKTroopa)->getState() == ENEMY_IDLE)
						{
							if (_player->getX() < (*_viKTroopa)->getX())
							{
								es = ENEMY_RIGHT_WALK;
							}
							else
							{
								es = ENEMY_LEFT_WALK;
							}
						}
						else
						{
							es = ENEMY_IDLE;
						}
					}
					_player->setY(_player->getY() - height);
					(*_viKTroopa)->setState(es);
					_player->setPlayerState(new playerJump);
					_player->getPlayerState()->enter(_player);
					break;
				}
				//아래에서 충돌
				else
				{
					if (_player->getPlayerShape() == BASIC)
					{
						_player->setPlayerState(new playerDie);
						_player->getPlayerState()->enter(_player);
					}
				}
			}
			else
			{
				//왼쪽에서 충돌
				if (_player->getX() < (*_viKTroopa)->getX())
				{
					//등껍질 상태이면
					if ((*_viKTroopa)->getIsShell())
					{
						//멈춰있으면 등껍질 움직이게함
						if ((*_viKTroopa)->getState() == ENEMY_IDLE)
						{
							es = ENEMY_RIGHT_WALK;
							_player->setX(_player->getX() - width);
						}
						else //움직이는 중에 부딪혔다면 player 죽음
						{
							if (_player->getPlayerShape() == BASIC)
							{
								_player->setPlayerState(new playerDie);
								_player->getPlayerState()->enter(_player);
							}
						}
					}
					else
					{
						if (_player->getPlayerShape() == BASIC)
						{
							_player->setPlayerState(new playerDie);
							_player->getPlayerState()->enter(_player);
						}
					}
					(*_viKTroopa)->setState(es);
					break;
				}
				else //오른쪽에서 충돌
				{
					//등껍질 상태이면
					if ((*_viKTroopa)->getIsShell())
					{
						//멈춰있으면 등껍질 움직이게함
						if ((*_viKTroopa)->getState() == ENEMY_IDLE)
						{
							es = ENEMY_LEFT_WALK;
							_player->setX(_player->getX() + width);
						}
						else //움직이는 중에 부딪혔다면 player 죽음
						{
							if (_player->getPlayerShape() == BASIC)
							{
								_player->setPlayerState(new playerDie);
								_player->getPlayerState()->enter(_player);
							}
						}
					}
					else
					{
						if (_player->getPlayerShape() == BASIC)
						{
							_player->setPlayerState(new playerDie);
							_player->getPlayerState()->enter(_player);
						}
					}
					(*_viKTroopa)->setState(es);
					break;
				}
				
			}
		}
	}

	//땅과 충돌
	for (_viKTroopa = _vKTroopa.begin(); _viKTroopa != _vKTroopa.end(); ++_viKTroopa)
	{
		RECT troopaRect = (*_viKTroopa)->getRect();
		(*_viKTroopa)->setIsOnGround(false);
		for (int i = 0; i < _mManager->getGround().size(); i++)
		{
			RECT ground = _mManager->getGround()[i];
			RECT temp;
			if (troopaRect.bottom == ground.top && troopaRect.right > ground.left && troopaRect.left < ground.right)
			{
				(*_viKTroopa)->setIsOnGround(true);
			}
			if (IntersectRect(&temp, &troopaRect, &ground))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				if (width > height)
				{
					//위에서 충돌
					if ((*_viKTroopa)->getY() < (ground.bottom + ground.top) / 2)
					{
						(*_viKTroopa)->setY((*_viKTroopa)->getY() - height);
						(*_viKTroopa)->setIsOnGround(true);
					}
					//땅과는 아래에서 충돌 없음
				}
				else
				{
					if ((*_viKTroopa)->getX() < (ground.left + ground.right) / 2)
					{
						(*_viKTroopa)->setX((*_viKTroopa)->getX() - width);
						if ((*_viKTroopa)->getState() == ENEMY_RIGHT_WALK)
						{
							(*_viKTroopa)->setState(ENEMY_LEFT_WALK);
						}
						else
						{
							(*_viKTroopa)->setState(ENEMY_LEFT_JUMP);
						}
					}
					else
					{
						(*_viKTroopa)->setX((*_viKTroopa)->getX() + width);
						if ((*_viKTroopa)->getState() == ENEMY_LEFT_WALK)
						{
							(*_viKTroopa)->setState(ENEMY_RIGHT_WALK);
						}
						else
						{
							(*_viKTroopa)->setState(ENEMY_RIGHT_JUMP);
						}
					}
				}
			}
		}
	}

	//object 와 충돌
	for (_viKTroopa = _vKTroopa.begin(); _viKTroopa != _vKTroopa.end(); ++_viKTroopa)
	{
		RECT troopaRect = (*_viKTroopa)->getRect();
		for (int i = 0; i < _mManager->getObject().size(); i++)
		{
			RECT object = _mManager->getObject()[i];
			RECT temp;
			if (troopaRect.bottom == object.top && troopaRect.right > object.left && troopaRect.left < object.right)
			{
				(*_viKTroopa)->setIsOnGround(true);
				break;
			}
			if (IntersectRect(&temp, &troopaRect, &object))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				if (width > height)
				{
					//위에서 충돌
					if ((*_viKTroopa)->getY() < (object.bottom + object.top) / 2)
					{
						(*_viKTroopa)->setY((*_viKTroopa)->getY() - height);
						(*_viKTroopa)->setIsOnGround(true);
						break;
					}
					//object와는 아래에서 충돌 없음
				}
			}
		}
	}

	//pipe와 충돌
	for (_viKTroopa = _vKTroopa.begin(); _viKTroopa != _vKTroopa.end(); ++_viKTroopa)
	{
		RECT troopaRect = (*_viKTroopa)->getRect();
		for (int i = 0; i < _mManager->getPipe().size(); i++)
		{
			RECT pipe_head = _mManager->getPipe()[i].head;
			RECT pipe_body = _mManager->getPipe()[i].body;
			RECT temp;
			if (troopaRect.bottom == pipe_head.top && troopaRect.right > pipe_head.left && troopaRect.left < pipe_head.right)
			{
				(*_viKTroopa)->setIsOnGround(true);
				break;
			}
			if (IntersectRect(&temp, &troopaRect, &pipe_head))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				if (width > height)
				{
					//위에서 충돌
					if ((*_viKTroopa)->getY() < (pipe_head.bottom + pipe_head.top) / 2)
					{
						(*_viKTroopa)->setY((*_viKTroopa)->getY() - height);
						(*_viKTroopa)->setIsOnGround(true);
						break;
					}
					//아래에서 충돌
					else
					{
						(*_viKTroopa)->setY((*_viKTroopa)->getY() + height);
						break;
					}
				}
				//좌우 충돌
				else
				{
					//왼쪽에서 충돌
					if ((*_viKTroopa)->getX() < (pipe_head.left + pipe_head.right) / 2)
					{
						(*_viKTroopa)->setX((*_viKTroopa)->getX() - width);
						if ((*_viKTroopa)->getState() == ENEMY_RIGHT_WALK)
						{
							(*_viKTroopa)->setState(ENEMY_LEFT_WALK);
						}
						else
						{
							(*_viKTroopa)->setState(ENEMY_LEFT_JUMP);
						}
					}
					//오른쪽에서 충돌
					else
					{
						(*_viKTroopa)->setX((*_viKTroopa)->getX() + width);
						if ((*_viKTroopa)->getState() == ENEMY_LEFT_WALK)
						{
							(*_viKTroopa)->setState(ENEMY_RIGHT_WALK);
						}
						else
						{
							(*_viKTroopa)->setState(ENEMY_RIGHT_JUMP);
						}
					}
				}
			}

			if (IntersectRect(&temp, &troopaRect, &pipe_body))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				//파이프 body는 위아래 충돌 없음
				if (width < height)
				{
					if ((*_viKTroopa)->getX() < (pipe_body.left + pipe_body.right) / 2)
					{
						(*_viKTroopa)->setX((*_viKTroopa)->getX() - width);
						if ((*_viKTroopa)->getState() == ENEMY_RIGHT_WALK)
						{
							(*_viKTroopa)->setState(ENEMY_LEFT_WALK);
						}
						else
						{
							(*_viKTroopa)->setState(ENEMY_LEFT_JUMP);
						}
					}
					else
					{
						(*_viKTroopa)->setX((*_viKTroopa)->getX() + width);
						if ((*_viKTroopa)->getState() == ENEMY_LEFT_WALK)
						{
							(*_viKTroopa)->setState(ENEMY_RIGHT_WALK);
						}
						else
						{
							(*_viKTroopa)->setState(ENEMY_RIGHT_JUMP);
						}
					}
				}
			}
		}
	}

	//question_block과 충돌
	for (_viKTroopa = _vKTroopa.begin(); _viKTroopa != _vKTroopa.end(); ++_viKTroopa)
	{
		RECT troopaRect = (*_viKTroopa)->getRect();
		for (int i = 0; i < _bManager->getQBlock().size(); i++)
		{
			RECT qBlock = _bManager->getQBlock()[i]->getRect();
			RECT temp;
			if (troopaRect.bottom == qBlock.top && troopaRect.right > qBlock.left && troopaRect.left < qBlock.right)
			{
				(*_viKTroopa)->setIsOnGround(true);
				break;
			}
			if (IntersectRect(&temp, &troopaRect, &qBlock))
			{
				if (!_bManager->getQBlock()[i]->getIsCrashed() && (*_viKTroopa)->getIsShell())
				{
					_bManager->getQBlock()[i]->setIsChange(true);
					//코인
					if (_bManager->getQBlock()[i]->getItem() == COIN)
					{
						_bManager->getCoin()->fire((qBlock.right + qBlock.left) / 2, (qBlock.bottom + qBlock.top) / 2);
					}
				}
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				if (width > height)
				{
					//위에서 충돌
					if ((*_viKTroopa)->getY() < (qBlock.bottom + qBlock.top) / 2)
					{
						(*_viKTroopa)->setY((*_viKTroopa)->getY() - height);
						(*_viKTroopa)->setIsOnGround(true);
						break;
					}
					//아래에서 충돌
					else
					{
						(*_viKTroopa)->setY((*_viKTroopa)->getY() + height);
						break;
					}
				}
				//좌우 충돌
				else
				{
					//왼쪽에서 충돌
					if ((*_viKTroopa)->getX() < (qBlock.left + qBlock.right) / 2)
					{
						(*_viKTroopa)->setX((*_viKTroopa)->getX() - width);
						if ((*_viKTroopa)->getState() == ENEMY_RIGHT_WALK)
						{
							(*_viKTroopa)->setState(ENEMY_LEFT_WALK);
						}
						else
						{
							(*_viKTroopa)->setState(ENEMY_LEFT_JUMP);
						}
					}
					//오른쪽에서 충돌
					else
					{
						(*_viKTroopa)->setX((*_viKTroopa)->getX() + width);
						if ((*_viKTroopa)->getState() == ENEMY_LEFT_WALK)
						{
							(*_viKTroopa)->setState(ENEMY_RIGHT_WALK);
						}
						else
						{
							(*_viKTroopa)->setState(ENEMY_RIGHT_JUMP);
						}
					}
				}
			}
		}
	}
}

void enemyManager::flowerCollison()
{
	for (_viFlower = _vFlower.begin(); _viFlower != _vFlower.end(); ++_viFlower)
	{
		if (_player->getPlayerState()->getStateName() == PLAYER_DIE) break;
		RECT flowerRangeRect = (*_viFlower)->getCollisonRange();
		RECT flowerRect = (*_viFlower)->getRect();
		RECT playerRect = _player->getRect();

		//꽃 나오지 않는 범위 확인용
		if (playerRect.left >= flowerRangeRect.left && playerRect.right <= flowerRangeRect.right
			&&playerRect.top >= flowerRangeRect.top && playerRect.bottom <= flowerRangeRect.bottom)
		{
			(*_viFlower)->setIsVisible(false);
		}
		else
		{
			(*_viFlower)->setIsVisible(true);
		}

		//플레이어 꽃과 충돌
		RECT temp;
		if (IntersectRect(&temp, &flowerRect, &playerRect))
		{
			if (_player->getPlayerShape() == BASIC)
			{
				_player->setPlayerState(new playerDie);
				_player->getPlayerState()->enter(_player);
			}
		}
	}

}

void enemyManager::flowerBulletFire()
{
	for (_viFlower = _vFlower.begin(); _viFlower != _vFlower.end(); ++_viFlower)
	{
		if (_player->getPlayerState()->getStateName() == PLAYER_DIE) break;

		if ((*_viFlower)->bulletCountFire())
		{
			if ((*_viFlower)->getIsVisible())
			{
				float angle = getAngle((*_viFlower)->getX(), (*_viFlower)->getY(), _player->getX(), _player->getY());
				_bullet->fire((*_viFlower)->getX(), (*_viFlower)->getY(), angle, 4.0f);
			}
			(*_viFlower)->setState(ENEMY_RIGHT_WALK);
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
