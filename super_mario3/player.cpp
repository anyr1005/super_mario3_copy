#include "stdafx.h"
#include "player.h"
#include "playerIdle.h"
#include "playerFall.h"
#include "playerChange.h"
#include "playerDie.h"

HRESULT player::init()
{
	//기본 마리오
	IMAGEMANAGER->addFrameImage("mario_walk", "img/mario/mario_walk.bmp", 90, 96, 2, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("mario_skid", "img/mario/mario_skid.bmp", 42, 96, 1, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("mario_run", "img/mario/mario_run.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("mario_jump", "img/mario/mario_jump.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("mario_run_jump", "img/mario/mario_run_jump.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("mario_idle", "img/mario/mario_idle.bmp", 36, 90, 1, 2, true, RGB(255, 0, 255), TRUE);

	//슈퍼마리오
	IMAGEMANAGER->addFrameImage("super_walk", "img/mario/super_mario_walk.bmp", 144, 162, 3, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("super_run", "img/mario/super_mario_run.bmp", 171, 162, 3, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("super_jump", "img/mario/super_mario_jump.bmp", 48, 156, 1, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("super_skid", "img/mario/super_mario_skid.bmp", 48, 168, 1, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("super_run_jump", "img/mario/super_mario_run_jump.bmp", 57, 156, 1, 2, true, RGB(255, 0, 255), TRUE);

	//꼬리마리오
	IMAGEMANAGER->addFrameImage("tail_walk", "img/mario/tail_mario_walk.bmp", 207, 168, 3, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("tail_run", "img/mario/tail_mario_run.bmp", 216, 168, 3, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("tail_jump", "img/mario/tail_mario_jump.bmp", 69, 162, 1, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("tail_skid", "img/mario/tail_mario_skid.bmp", 48, 180, 1, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("tail_run_jump", "img/mario/tail_mario_run_jump.bmp", 72, 168, 1, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("tail_fly", "img/mario/tail_mario_fly.bmp", 216, 168, 3, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("tail_attack", "img/mario/tail_mario_attack.bmp", 360, 168, 4, 2, true, RGB(255, 0, 255), TRUE);

	//변신
	IMAGEMANAGER->addFrameImage("mario_grow", "img/mario/mario_grow_frame.bmp", 546, 162, 13, 2, true, RGB(255, 0, 255), TRUE);
	IMAGEMANAGER->addFrameImage("mario_change", "img/mario/change_effect.bmp", 288, 48, 6, 1, true, RGB(0, 0, 0), TRUE);

	//죽음
	IMAGEMANAGER->addFrameImage("mario_die", "img/mario/mario_die.bmp", 48, 48, 1, 1, true, RGB(255, 0, 255), TRUE);

	_isRight = true;

	_shape = TAIL;

	_state = new playerIdle;
	_state->enter(this);

	//_shape = BASIC;
	

	//_x = 100;
	//_y = BACKGROUNDY - 72;

	_x = 1649;
	_y = 890;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_runSpeed = BASICSPEED;

	_isLRCollison = false;
	_isOnGround = true;

	_isAttacked = false;
	_attackedCount = 0;

	_alphaValue = 255;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_isOnGround = false;
	_isLRCollison = false;

	if (_state->getStateName() != PLAYER_DIE)
	{
		collisonGround();
		collisonObject();
		collisonPipe();
		collisonQBlock();
		collisonGBlock();
		collisonWoodBlock();
		collisonMushroom();
		collisonLeaf();
	}
	
	if (_shape == SUPER)
	{
		_bManager->setIsLeaf(true);
	}
	else
	{
		_bManager->setIsLeaf(false);
	}

	handleInput();
	_state->update(this);
	
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_isAttacked = true;
		_state = new playerChange;
		_state->enter(this);
	}

	if (_isAttacked)
	{
		_attackedCount++;
		if (_attackedCount >= 200)
		{
			_isAttacked = false;
		}
		if (_attackedCount % 5 == 0)
		{
			if (_alphaValue == 255)
				_alphaValue = 0;
			else
				_alphaValue = 255;
		}
	}
	else
	{
		_alphaValue = 255;
	}

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_isAttacked = true;
	}
}

void player::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);

		char str[128];
		sprintf_s(str, "땅에 있나? %d x좌표 : %f y좌표 : %f", _isOnGround, _x, _y);
		TextOut(getMemDC(), _rc.left - 100, _rc.top - 20, str, strlen(str));
	}
	_img->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _alphaValue);
}


void player::handleInput()
{
	playerState* state = _state->handleInput(this);
	if (state != NULL)
	{
		SAFE_DELETE(_state);
		_state = state;
		_state->enter(this);
	}
}

void player::collisonGround()
{	
	for (int i = 0; i < _mManager->getGround().size(); i++)
	{
		RECT temp;
		RECT ground = _mManager->getGround()[i];
		if (_rc.bottom == ground.top && _rc.right > ground.left && _rc.left < ground.right)
		{
			_isOnGround = true;
		}
		if (IntersectRect(&temp, &ground, &_rc))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			//상하 충돌
			if (width > height)
			{
				//위에서 아래로 충돌
				if (_y < (ground.top + ground.bottom) / 2)
				{
					_y -= height;
					_isOnGround = true;
				}
			}
			//좌우 충돌
			else
			{
				_isLRCollison = true;
				//왼쪽에서 충돌
				if (_x < (ground.left + ground.right) / 2)
				{
					_x -= width;
				}
				//오른쪽에서 충돌
				else
				{
					_x += width;
				}
			}
		}
	}
}

void player::collisonObject()
{
	for (int i = 0; i < _mManager->getObject().size(); i++)
	{
		RECT temp;
		RECT object = _mManager->getObject()[i];
		if (_rc.bottom == object.top && _rc.right > object.left && _rc.left < object.right) _isOnGround = true;
		if (IntersectRect(&temp, &object, &_rc))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			//상하 충돌
			if (width > height)
			{
				//위에서 아래로 충돌
				if ((_rc.top + _rc.bottom) / 2 < (object.top + object.bottom) / 2 && _jumpPower < 0)
				{
					_y -= height;
					_isOnGround = true;
					break;
				}
				//아래에서 충돌처리 없음
			}
			//좌우 충돌 없음
		}
	}
}

void player::collisonPipe()
{
	for (int i = 0; i < _mManager->getPipe().size(); i++)
	{
		RECT temp;
		RECT head = _mManager->getPipe()[i].head;
		if (_rc.bottom == head.top && _rc.right > head.left && _rc.left < head.right) _isOnGround = true;
		if (IntersectRect(&temp, &head, &_rc))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			//상하 충돌
			if (width > height)
			{
				//위에서 아래로 충돌
				if ((_rc.top + _rc.bottom) / 2 < (head.top + head.bottom) / 2)
				{
					_y -= height;
					_isOnGround = true;
					//break;
				}
			}
			//좌우 충돌
			else
			{
				_isLRCollison = true;
				//왼쪽에서 충돌
				if ((_rc.left + _rc.right) / 2 < (head.left + head.right) / 2)
				{
					_x -= width;
					break;
				}
				//오른쪽에서 충돌
				else
				{
					_x += width;
					break;
				}
			}
		}
	}
	for (int i = 0; i < _mManager->getPipe().size(); i++)
	{
		RECT temp;
		RECT body = _mManager->getPipe()[i].body;
		if (IntersectRect(&temp, &body, &_rc))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			//좌우 충돌(상하 충돌 없음)
			if (width <= height)
			{
				_isLRCollison = true;
				//왼쪽에서 충돌
				if ((_rc.left + _rc.right) / 2 < (body.left + body.right) / 2)
				{
					_x -= width;
					break;
				}
				//오른쪽에서 충돌
				else
				{
					_x += width;
					break;
				}
			}
		}
	}
	
}

void player::collisonWoodBlock()
{
	for (int i = 0; i < _mManager->getWoodBlock().size(); i++)
	{
		RECT temp;
		RECT block = _mManager->getWoodBlock()[i];
		if (_rc.bottom == block.top && _rc.right > block.left && _rc.left < block.right)
		{
			_isOnGround = true;
		}
		if (IntersectRect(&temp, &block, &_rc))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			if (width > height)
			{
				//위에서 아래로 충돌
				if (_y < (block.top + block.bottom) / 2)
				{
					_y -= height;
					_isOnGround = true;
				}
				else
				{
					_y += height;
					_state = new playerFall;
					_state->enter(this);
				}
			}
			else
			{
				if (_x < (block.right + block.left) / 2)
				{
					_x -= width;
				}
				else
				{
					_x += width;
				}
			}
		}
	}
}

void player::collisonQBlock()
{
	for (int i = 0; i < _bManager->getQBlock().size(); i++)
	{
		RECT temp;
		RECT qBlock = _bManager->getQBlock()[i]->getRect();
		if (_rc.bottom == qBlock.top && _rc.right > qBlock.left && _rc.left < qBlock.right)
		{
			_isOnGround = true;
			break;
		}
		if (IntersectRect(&temp, &qBlock, &_rc))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			//상하 충돌
			if (width > height)
			{
				//위에서 아래로 충돌
				if (_y < (qBlock.top + qBlock.bottom) / 2)
				{
					_y -= height;
					_isOnGround = true;
					break;
				}
				//아래에서 위로 충돌
				else
				{
					if (!_bManager->getQBlock()[i]->getIsCrashed())
					{
						if (_x < (qBlock.right + qBlock.left)/2)
						{
							_bManager->setIsRight(true);
						}
						else
						{
							_bManager->setIsRight(false);
						}
						_bManager->getQBlock()[i]->setIsChange(true);
						//코인
						if (_bManager->getQBlock()[i]->getItem() == COIN)
						{
							_bManager->getCoin()->fire((qBlock.right + qBlock.left) / 2, (qBlock.bottom + qBlock.top) / 2);
						}
					}

					_y += height;
					_state = new playerFall;
					_state->enter(this);
					break;
				}
			}
			//좌우 충돌
			else
			{
				_isLRCollison = true;
				//왼쪽에서 충돌
				if (_x < (qBlock.left + qBlock.right) / 2)
				{
					_x -= width;
					break;
				}
				//오른쪽에서 충돌
				else
				{
					_x += width;
					break;
				}
			}
			
		}
	}
}

//수정필요
void player::collisonGBlock()
{
	for (int i = 0; i < _bManager->getGBlock().size(); i++)
	{
		RECT temp;
		RECT gBlock = _bManager->getGBlock()[i]->getRect();
		if (_rc.bottom == gBlock.top && _rc.right > gBlock.left && _rc.left < gBlock.right)
		{
			_isOnGround = true;
			break;
		}
		if (IntersectRect(&temp, &gBlock, &_rc))
		{
			float width = temp.right - temp.left;
			float height = temp.bottom - temp.top;
			//상하 충돌
			if (width > height)
			{
				//위에서 아래로 충돌
				if ((_rc.top + _rc.bottom) / 2 < (gBlock.top + gBlock.bottom) / 2)
				{
					_y -= height;
					_isOnGround = true;
				}
				//아래에서 위로 충돌
				else
				{
					/*
					RECT rc = _bManager->getGBlock()[i]->getRect();
					if (!_bManager->getGBlock()[i]->getIsCrashed())
					{
						_bManager->getGBlock()[i]->setIsChange(true);
						//코인
						_bManager->getCoin()->fire((rc.right + rc.left) / 2, (rc.bottom + rc.top) / 2);
					}
					*/
					_y+= height;
					_state = new playerFall;
					_state->enter(this);
				}
			}
			//좌우 충돌
			else
			{
				_isLRCollison = true;
				//왼쪽에서 충돌
				if ((_rc.left + _rc.right) / 2 < (gBlock.left + gBlock.right) / 2)
				{
					_x -= width;
				}
				//오른쪽에서 충돌
				else
				{
					_x += width;
				}
			}

		}
	}
}

//슈퍼버섯 먹으면
void player::collisonMushroom()
{
	for (int i = 0; i < _bManager->getMushroom()->getVMushroom().size(); i++)
	{
		RECT temp;
		RECT mushroom = _bManager->getMushroom()->getVMushroom()[i].rc;
		if (IntersectRect(&temp, &_rc, &mushroom))
		{
			_state = new playerChange;
			_state->enter(this);
			_bManager->getMushroom()->removeMushroom(i);
			_isAttacked = false;
			break;
		}
	}
}

void player::collisonLeaf()
{
	for (int i = 0; i < _bManager->getLeaf()->getVLeaf().size(); i++)
	{
		RECT temp;
		RECT leaf = _bManager->getLeaf()->getVLeaf()[i].rc;
		if (IntersectRect(&temp, &_rc, &leaf))
		{
			_state = new playerChange;
			_state->enter(this);
			_bManager->getLeaf()->removeLeaf(i);
			_isAttacked = false;
			break;
		}
	}
}



