#include "stdafx.h"
#include "blockManager.h"

HRESULT blockManager::init()
{
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
}

void blockManager::render()
{
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
}

void blockManager::setQuestionBlock()
{
	for (int i = 0; i < 2; i++)
	{
		question_block* qBlock;
		qBlock = new question_block;
		qBlock->init("qBlock", PointMake(552 + 48 * i, BACKGROUNDY - 216));
		_vQBlock.push_back(qBlock);
	}

	for (int i = 0; i < 3; i++)
	{
		question_block* qBlock;
		qBlock = new question_block;
		if (i == 2)
		{
			qBlock->init("qBlock", PointMake(1272, BACKGROUNDY - 312));
		}
		else
		{
			qBlock->init("qBlock", PointMake(696 + 48 * i, BACKGROUNDY - 360));
		}
		_vQBlock.push_back(qBlock);

	}

	for (int i = 0; i < 3; i++)
	{
		question_block* qBlock;
		qBlock = new question_block;
		if (i == 2)
		{
			qBlock->init("qBlock", PointMake(BACKGROUNDX / 2 + 264, BACKGROUNDY - 168));
		}
		else
		{
			qBlock->init("qBlock", PointMake(1992 + 144 * i, BACKGROUNDY - 120 - 96 * i));
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

	for (int i = 0; i < 5; i++)
	{
		golden_block* gBlock;
		gBlock = new golden_block;
		if (i == 4)
		{
			gBlock->init("gBlock", PointMake(BACKGROUNDX / 2 + 168, 408));
		}
		else
		{
			gBlock->init("gBlock", PointMake(BACKGROUNDX - 2472 + 48 * i, BACKGROUNDY - 168));
		}

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
