#include "stdafx.h"
#include "blockManager.h"

HRESULT blockManager::init()
{
	IMAGEMANAGER->addFrameImage("qBlock", "img/block/question_block.bmp", 192, 48, 4, 1, true, RGB(255, 0, 255), FALSE);
	IMAGEMANAGER->addFrameImage("gBlock", "img/block/golden_block.bmp", 192, 48, 4, 1, true, RGB(255, 0, 255), FALSE);
	IMAGEMANAGER->addFrameImage("coin", "img/block/coin.bmp", 168, 48, 4, 1, true, RGB(255, 0, 255), FALSE);
	IMAGEMANAGER->addFrameImage("q_change", "img/block/question_box_change.bmp", 48, 48, 1, 1, true, RGB(255, 0, 255), FALSE);
	IMAGEMANAGER->addFrameImage("q_change_complete", "img/block/question_box_change_complete.bmp", 48, 48, 1, 1, true, RGB(255, 0, 255), FALSE);

	IMAGEMANAGER->addImage("mushroom", "img/item/mushroom.bmp", 48, 48, true, RGB(255, 0, 255), FALSE);
	IMAGEMANAGER->addFrameImage("leaf", "img/item/leaf.bmp", 48, 84, 1, 2, true, RGB(255, 0, 255), FALSE);
	IMAGEMANAGER->addFrameImage("particle", "img/item/particle.bmp", 96, 24, 4, 1, true, RGB(255, 0, 255), FALSE);
	IMAGEMANAGER->addImage("life", "img/item/life.bmp", 48, 48, true, RGB(255, 0, 255), FALSE);

	_coin = new coin;
	_coin->init();

	_mushroom = new mushroom;
	_mushroom->init();

	_leaf = new leaf;
	_leaf->init();

	_particle = new particle;
	_particle->init();

	setQuestionBlock();
	setGoldenBlock();
	setCoinBlock();
	return S_OK;
}

void blockManager::release()
{
}

void blockManager::update()
{

	for (_viQBlock = _vQBlock.begin(); _viQBlock != _vQBlock.end(); ++_viQBlock)
	{
		if (!(*_viQBlock)->getIsFire() && (*_viQBlock)->getIsCrashed())
		{
			RECT rc = (*_viQBlock)->getRect();
			if ((*_viQBlock)->getItem() == MUSHROOM)
			{
				//슈퍼버섯
				_mushroom->fire((rc.right + rc.left) / 2, (rc.bottom + rc.top) / 2, _isRight, false);
				(*_viQBlock)->setIsFire(true);
			}
			else if ((*_viQBlock)->getItem() == LIFE)
			{
				//슈퍼버섯
				_mushroom->fire((rc.right + rc.left) / 2, (rc.bottom + rc.top) / 2, _isRight, true);
				(*_viQBlock)->setIsFire(true);
			}
		}
		(*_viQBlock)->update();
	}
	for (_viGBlock = _vGBlock.begin(); _viGBlock != _vGBlock.end(); ++_viGBlock)
	{
		(*_viGBlock)->update();
	}
	for (_viCoinBlock = _vCoinBlock.begin(); _viCoinBlock != _vCoinBlock.end(); ++_viCoinBlock)
	{
		(*_viCoinBlock)->update();
	}

	_coin->update();
	_mushroom->update();
	_leaf->update();
	_particle->update();

	mushroomCollision();
	//leafCollision();

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_particle->fire(300, 1226);
	}
}

void blockManager::render()
{
	_coin->render();
	_mushroom->render();
	for (_viQBlock = _vQBlock.begin(); _viQBlock != _vQBlock.end(); ++_viQBlock)
	{
		(*_viQBlock)->render();
	}

	for (_viGBlock = _vGBlock.begin(); _viGBlock != _vGBlock.end(); ++_viGBlock)
	{
		(*_viGBlock)->render();
	}

	for (_viCoinBlock = _vCoinBlock.begin(); _viCoinBlock != _vCoinBlock.end(); ++_viCoinBlock)
	{
		(*_viCoinBlock)->render();
	}
	
	_leaf->render();
	_particle->render();
}

void blockManager::setQuestionBlock()
{
	for (int i = 0; i < 2; i++)
	{
		question_block* qBlock;
		qBlock = new question_block;
		qBlock->init("qBlock", PointMake(552 + 48 * i, BACKGROUNDY - 216));
		qBlock->setItem(COIN);
		_vQBlock.push_back(qBlock);
	}

	for (int i = 0; i < 3; i++)
	{
		question_block* qBlock;
		qBlock = new question_block;
		if (i == 2)
		{
			qBlock->init("qBlock", PointMake(1272, BACKGROUNDY - 312));
			qBlock->setItem(COIN);
		}
		else
		{
			qBlock->init("qBlock", PointMake(696 + 48 * i, BACKGROUNDY - 360));
			if (i == 1)
			{
				qBlock->setItem(MUSHROOM);
			}
			else
			{
				qBlock->setItem(COIN);
			}
		}
		_vQBlock.push_back(qBlock);

	}

	for (int i = 0; i < 4; i++)
	{
		question_block* qBlock;
		qBlock = new question_block;
		if (i == 3)
		{
			qBlock->init("gBlock", PointMake(BACKGROUNDX / 2 + 168, 408));
			qBlock->setItem(LIFE);
		}
		else if (i == 2)
		{
			qBlock->init("qBlock", PointMake(BACKGROUNDX / 2 + 264, BACKGROUNDY - 168));
			qBlock->setItem(MUSHROOM);
		}
		else
		{
			qBlock->init("qBlock", PointMake(1992 + 144 * i, BACKGROUNDY - 120 - 96 * i));
			if (i == 0)
			{
				qBlock->setItem(MUSHROOM);
			}
			else
			{
				qBlock->setItem(COIN);
			}
		}

		_vQBlock.push_back(qBlock);
	}
}

void blockManager::setGoldenBlock()
{
	for (int i = 0; i < 9; i++)
	{
		golden_block* gBlock;
		gBlock = new golden_block;
		if (i >= 7)
		{
			gBlock->init("gBlock", PointMake(BACKGROUNDX - 2568 + 48 * i + 96, BACKGROUNDY - 72));
		}
		else
		{
			gBlock->init("gBlock", PointMake(BACKGROUNDX - 2568 + 48 * i, BACKGROUNDY - 72));
		}
		_vGBlock.push_back(gBlock);
	}

	for (int i = 0; i < 6; i++)
	{
		golden_block* gBlock;
		gBlock = new golden_block;
		if (i == 5)
		{
			gBlock->init("gBlock", PointMake(BACKGROUNDX - 2520 + 48 * i + 144, BACKGROUNDY - 120));
		}
		else
		{
			gBlock->init("gBlock", PointMake(BACKGROUNDX - 2520 + 48 * i, BACKGROUNDY - 120));
		}
		_vGBlock.push_back(gBlock);
	}

	for (int i = 0; i < 4; i++)
	{
		golden_block* gBlock;
		gBlock = new golden_block;
		gBlock->init("gBlock", PointMake(BACKGROUNDX - 2472 + 48 * i, BACKGROUNDY - 168));

		_vGBlock.push_back(gBlock);
	}
}

void blockManager::setCoinBlock()
{
	for (int i = 0; i < 4; i++)
	{
		coin_block* coinBlock;
		coinBlock = new coin_block;
		coinBlock->init("coin", PointMake(BACKGROUNDX / 2 - 840 + 96 * i, BACKGROUNDY - 408 - 96 * i));
		_vCoinBlock.push_back(coinBlock);
	}
	for (int i = 0; i < 3; i++)
	{
		coin_block* coinBlock;
		coinBlock = new coin_block;
		coinBlock->init("coin", PointMake(BACKGROUNDX / 2 - 168 + 48 * i, 264));
		_vCoinBlock.push_back(coinBlock);
	}
	for (int i = 0; i < 14; i++)
	{
		coin_block* coinBlock;
		coinBlock = new coin_block;
		int x, y = 0;
		if (i == 13)
		{
			x = BACKGROUNDX / 2 + 648 + 48 * i;
			y = 408;
		}
		else if (i == 12)
		{
			x = BACKGROUNDX / 2 + 600 + 48 * i;
			y = 312;
		}
		else if (i == 11)
		{
			x = BACKGROUNDX / 2 + 504 + 48 * i;
			y = 408;
		}
		else if (i == 10)
		{
			x = BACKGROUNDX / 2 + 456 + 48 * i;
			y = 456;
		}
		else if (i >= 6)
		{
			x = BACKGROUNDX / 2 + 408 + 48 * i;
			y = 360;
		}
		else if (i >= 2)
		{
			x = BACKGROUNDX / 2 + 360 + 48 * i;
			y = 408;
		}
		else
		{
			x = BACKGROUNDX / 2 + 264 + 48 * i;
			y = 360;
		}
		coinBlock->init("coin", PointMake(x, y));
		_vCoinBlock.push_back(coinBlock);
	}
}

void blockManager::removeQuestionBlock(int arrNum)
{
	_vQBlock.erase(_vQBlock.begin() + arrNum);
}

void blockManager::removeGoldenBlock(int arrNum)
{
	_vGBlock.erase(_vGBlock.begin() + arrNum);
}

void blockManager::removeCoinBlock(int arrNum)
{
	_vCoinBlock.erase(_vCoinBlock.begin() + arrNum);
}

void blockManager::mushroomCollision()
{
	for (int i = 0; i < _mushroom->getVMushroom().size(); i++)
	{
		if (_mushroom->getVMushroom()[i].state == ITEM_UP) continue;

		RECT temp;
		RECT mushroomRect = _mushroom->getVMushroom()[i].rc;
		
		_mushroom->setIsOnGround(i, false);
		
		//question block과 충돌
		for (int j = 0; j < _vQBlock.size(); j++)
		{
			RECT qBlock = _vQBlock[j]->getRect();
			if (mushroomRect.bottom == qBlock.top && mushroomRect.right > qBlock.left && mushroomRect.left < qBlock.right)
			{
				_mushroom->setIsOnGround(i, true);
			}
			if (IntersectRect(&temp, &mushroomRect, &qBlock))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				//상하 충돌
				if (width > height)
				{
					//위에서 충돌
					if (_mushroom->getVMushroom()[i].y < (qBlock.top + qBlock.bottom) / 2)
					{
						_mushroom->setIsOnGround(i, true);
						_mushroom->setY(i, _mushroom->getVMushroom()[i].y - height);
					}
					//아래에서 충돌 없음
				}
				else //좌우 충돌
				{
					//왼쪽에서 충돌
					if (_mushroom->getVMushroom()[i].x < (qBlock.left + qBlock.right) / 2)
					{
						_mushroom->setX(i, _mushroom->getVMushroom()[i].x - width);
						_mushroom->setState(i, ITEM_LEFT);
					}
					else //오른쪽 충돌
					{
						_mushroom->setX(i, _mushroom->getVMushroom()[i].x + width);
						_mushroom->setState(i, ITEM_RIGHT);
					}
				}
			}
		}
		
		//땅과의 충돌
		for (int j = 0; j < _mManager->getGround().size(); j++)
		{
			RECT ground = _mManager->getGround()[j];
			if (mushroomRect.bottom == ground.top && mushroomRect.right > ground.left && mushroomRect.left < ground.right)
			{
				_mushroom->setIsOnGround(i, true);
			}
			if (IntersectRect(&temp, &mushroomRect, &ground))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				//상하 충돌
				if (width > height)
				{
					//위에서 충돌
					if (_mushroom->getVMushroom()[i].y < (ground.top + ground.bottom) / 2)
					{
						_mushroom->setIsOnGround(i, true);
						_mushroom->setY(i, _mushroom->getVMushroom()[i].y - height);
					}
					//아래에서 충돌 없음
				}
				else //좌우 충돌
				{
					//왼쪽에서 충돌
					if (_mushroom->getVMushroom()[i].x < (ground.left + ground.right) / 2)
					{
						_mushroom->setX(i, _mushroom->getVMushroom()[i].x - width);
						_mushroom->setState(i, ITEM_LEFT);
					}
					else //오른쪽 충돌
					{
						_mushroom->setX(i, _mushroom->getVMushroom()[i].x + width);
						_mushroom->setState(i, ITEM_RIGHT);
					}
				}
			}
		}
		
		//object와 충돌
		for (int j = 0; j < _mManager->getObject().size(); j++)
		{
			RECT object = _mManager->getObject()[j];
			if (mushroomRect.bottom == object.top && mushroomRect.right > object.left && mushroomRect.left < object.right)
			{
				_mushroom->setIsOnGround(i, true);
			}
			if (IntersectRect(&temp, &mushroomRect, &object))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				//상하 충돌
				if (width > height)
				{
					//위에서 충돌
					if (_mushroom->getVMushroom()[i].y < (object.top + object.bottom) / 2)
					{
						_mushroom->setIsOnGround(i, true);
						_mushroom->setY(i, _mushroom->getVMushroom()[i].y - height);
						break;
					}
					//아래에서 충돌 없음
				}
				//좌우 충돌 없음
			}
		}

		//파이프와 충돌
		for (int j = 0; j < _mManager->getPipe().size(); j++)
		{
			RECT head = _mManager->getPipe()[j].head;
			RECT body = _mManager->getPipe()[j].body;
			if (mushroomRect.bottom == head.top && mushroomRect.right > head.left && mushroomRect.left < head.right)
			{
				_mushroom->setIsOnGround(i, true);
			}
			if (IntersectRect(&temp, &mushroomRect, &head))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				//상하 충돌
				if (width > height)
				{
					//위에서 충돌
					if (_mushroom->getVMushroom()[i].y < (head.top + head.bottom) / 2)
					{
						_mushroom->setIsOnGround(i, true);
						_mushroom->setY(i, _mushroom->getVMushroom()[i].y - height);
						break;
					}
				}
				else //좌우 충돌
				{
					//왼쪽에서 충돌
					if (_mushroom->getVMushroom()[i].x < (head.left + head.right) / 2)
					{
						_mushroom->setX(i, _mushroom->getVMushroom()[i].x - width);
						_mushroom->setState(i, ITEM_LEFT);
						break;
					}
					else //오른쪽 충돌
					{
						_mushroom->setX(i, _mushroom->getVMushroom()[i].x + width);
						_mushroom->setState(i, ITEM_RIGHT);
						break;
					}
				}
			}

			if (IntersectRect(&temp, &mushroomRect, &body))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				//상하 충돌
				if (width > height)
				{
					//위에서 충돌
					if (_mushroom->getVMushroom()[i].y < (body.top + body.bottom) / 2)
					{
						_mushroom->setIsOnGround(i, true);
						_mushroom->setY(i, _mushroom->getVMushroom()[i].y - height);
						break;
					}
				}
				else //좌우 충돌
				{
					//왼쪽에서 충돌
					if (_mushroom->getVMushroom()[i].y < (body.top + body.bottom) / 2)
					{
						_mushroom->setX(i, _mushroom->getVMushroom()[i].x - width);
						_mushroom->setState(i, ITEM_LEFT);
						break;
					}
					else //오른쪽 충돌
					{
						_mushroom->setX(i, _mushroom->getVMushroom()[i].x + width);
						_mushroom->setState(i, ITEM_RIGHT);
						break;
					}
				}
				
			}
		}
	}
}

void blockManager::leafCollision()
{
	for (int i = 0; i < _leaf->getVLeaf().size(); i++)
	{
		if (_leaf->getVLeaf()[i].state == ITEM_UP) continue;

		RECT temp;
		RECT leafRect = _leaf->getVLeaf()[i].rc;

		_leaf->setIsOnGround(i, false);

		//question block과 충돌
		for (int j = 0; j < _vQBlock.size(); j++)
		{
			RECT qBlock = _vQBlock[j]->getRect();
			if (leafRect.bottom == qBlock.top && leafRect.right > qBlock.left && leafRect.left < qBlock.right)
			{
				_leaf->setState(i, ITEM_IDLE);
			}
			if (IntersectRect(&temp, &leafRect, &qBlock))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				//상하 충돌
				if (width > height)
				{
					//위에서 충돌
					if (_leaf->getVLeaf()[i].y < (qBlock.top + qBlock.bottom) / 2)
					{
						_leaf->setIsOnGround(i, true);
						_leaf->setY(i, _leaf->getVLeaf()[i].y - height);
					}
					//아래에서 충돌 없음
				}
				else //좌우 충돌
				{
					//왼쪽에서 충돌
					if (_leaf->getVLeaf()[i].x < (qBlock.left + qBlock.right) / 2)
					{
						_leaf->setX(i, _leaf->getVLeaf()[i].x - width);
						_leaf->setState(i, ITEM_LEFT);
					}
					else //오른쪽 충돌
					{
						_leaf->setX(i, _leaf->getVLeaf()[i].x + width);
						_leaf->setState(i, ITEM_RIGHT);
					}
				}
			}
		}

		//땅과의 충돌
		for (int j = 0; j < _mManager->getGround().size(); j++)
		{
			RECT ground = _mManager->getGround()[j];
			if (leafRect.bottom == ground.top && leafRect.right > ground.left && leafRect.left < ground.right)
			{
				_leaf->setState(i, ITEM_IDLE);
			}
			if (IntersectRect(&temp, &leafRect, &ground))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				//상하 충돌
				if (width > height)
				{
					//위에서 충돌
					if (_leaf->getVLeaf()[i].y < (ground.top + ground.bottom) / 2)
					{
						_leaf->setIsOnGround(i, true);
						_leaf->setY(i, _leaf->getVLeaf()[i].y - height);
					}
					//아래에서 충돌 없음
				}
				else //좌우 충돌
				{
					//왼쪽에서 충돌
					if (_leaf->getVLeaf()[i].x < (ground.left + ground.right) / 2)
					{
						_leaf->setX(i, _leaf->getVLeaf()[i].x - width);
						_leaf->setState(i, ITEM_LEFT);
					}
					else //오른쪽 충돌
					{
						_leaf->setX(i, _mushroom->getVMushroom()[i].x + width);
						_leaf->setState(i, ITEM_RIGHT);
					}
				}
			}
		}

		//object와 충돌
		for (int j = 0; j < _mManager->getObject().size(); j++)
		{
			RECT object = _mManager->getObject()[j];
			if (leafRect.bottom == object.top && leafRect.right > object.left && leafRect.left < object.right)
			{
				_leaf->setState(i, ITEM_IDLE);
			}
			if (IntersectRect(&temp, &leafRect, &object))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				//상하 충돌
				if (width > height)
				{
					//위에서 충돌
					if (_leaf->getVLeaf()[i].y < (object.top + object.bottom) / 2)
					{
						_leaf->setIsOnGround(i, true);
						_leaf->setY(i, _leaf->getVLeaf()[i].y - height);
						break;
					}
					//아래에서 충돌 없음
				}
				//좌우 충돌 없음
			}
		}

		//파이프와 충돌
		for (int j = 0; j < _mManager->getPipe().size(); j++)
		{
			RECT head = _mManager->getPipe()[j].head;
			RECT body = _mManager->getPipe()[j].body;
			if (leafRect.bottom == head.top && leafRect.right > head.left && leafRect.left < head.right)
			{
				_leaf->setState(i, ITEM_IDLE);
			}
			if (IntersectRect(&temp, &leafRect, &head))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				//상하 충돌
				if (width > height)
				{
					//위에서 충돌
					if (_leaf->getVLeaf()[i].y < (head.top + head.bottom) / 2)
					{
						_leaf->setIsOnGround(i, true);
						_leaf->setY(i, _leaf->getVLeaf()[i].y - height);
						break;
					}
				}
				else //좌우 충돌
				{
					//왼쪽에서 충돌
					if (_leaf->getVLeaf()[i].x < (head.left + head.right) / 2)
					{
						_leaf->setX(i, _leaf->getVLeaf()[i].x - width);
						_leaf->setState(i, ITEM_LEFT);
						break;
					}
					else //오른쪽 충돌
					{
						_leaf->setX(i, _leaf->getVLeaf()[i].x + width);
						_leaf->setState(i, ITEM_RIGHT);
						break;
					}
				}
			}

			if (IntersectRect(&temp, &leafRect, &body))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;
				//좌우 충돌
				if (width < height)
				{
					//왼쪽에서 충돌
					if (_leaf->getVLeaf()[i].y < (body.top + body.bottom) / 2)
					{
						_leaf->setX(i, _leaf->getVLeaf()[i].x - width);
						_leaf->setState(i, ITEM_LEFT);
						break;
					}
					else //오른쪽 충돌
					{
						_leaf->setX(i, _mushroom->getVMushroom()[i].x + width);
						_leaf->setState(i, ITEM_RIGHT);
						break;
					}
				}
			}
		}
	}
}
