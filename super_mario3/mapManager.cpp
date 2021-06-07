#include "stdafx.h"
#include "mapManager.h"

HRESULT mapManager::init()
{
	setQuestionBlock();
	setGoldenBlock();
	setCoinBlock();
	setObject();
	setWoodBlock();
	return S_OK;
}

void mapManager::release()
{
}

void mapManager::update()
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

void mapManager::render()
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
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < OBJECTMAX; i++)
		{
			Rectangle(getMemDC(), _object[i]);
		}
		for (int i = 0; i < WOODBLOCKMAX; i++)
		{
			Rectangle(getMemDC(), _woodBlock[i]);
		}
	}
}

void mapManager::setQuestionBlock()
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

void mapManager::setGoldenBlock()
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

void mapManager::setCoinBlock()
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

void mapManager::setObject()
{
	_object[0] = RectMake(720, BACKGROUNDY - 192, 144, 30);
	_object[1] = RectMake(816, BACKGROUNDY - 288, 144, 30);

	_object[2] = RectMake(1200, BACKGROUNDY - 192, 240, 30);
	_object[3] = RectMake(1392, BACKGROUNDY - 288, 192, 30);
	_object[4] = RectMake(1536, BACKGROUNDY - 384, 192, 30);
	_object[5] = RectMake(1536, BACKGROUNDY - 144, 288, 30);

	for (int i = 6; i < 9; i++)
	{
		_object[i] = RectMake(BACKGROUNDX / 2 - 384 + 96 * (i % 6), BACKGROUNDY - 144 - 96 * (i % 6), 336, 30);
	}
	_object[9] = RectMake(BACKGROUNDX - 2016, BACKGROUNDY - 192, 144, 30);
	_object[10] = RectMake(BACKGROUNDX - 1920, BACKGROUNDY - 480, 144, 30);

	//하늘에 있는 부유물
	_object[11] = RectMake(BACKGROUNDX / 2 - 240, 432, 192, 30);

	//구름
	_object[12] = RectMake(BACKGROUNDX / 2 + 48, 576, 192, 48);
	_object[13] = RectMake(BACKGROUNDX / 2 + 288, 528, 624, 48);

}

void mapManager::setWoodBlock()
{
	_woodBlock[0] = RectMake(BACKGROUNDX / 2 + 336, BACKGROUNDY - 288, 96, 48);
	_woodBlock[1] = RectMake(BACKGROUNDX / 2 + 528, BACKGROUNDY - 96, 144, 48);
	_woodBlock[2] = RectMake(BACKGROUNDX / 2 + 528 + 48, BACKGROUNDY - 144, 96, 48);
	_woodBlock[3] = RectMake(BACKGROUNDX / 2 + 528 + 48 + 48, BACKGROUNDY - 144 - 48, 48, 48);
	_woodBlock[4] = RectMake(BACKGROUNDX / 2 + 528 + 48 + 48 + 192, BACKGROUNDY - 144 - 48, 48, 48);
	_woodBlock[5] = RectMake(BACKGROUNDX / 2 + 528 + 48 + 48 + 192, BACKGROUNDY - 144, 96, 48);
	_woodBlock[6] = RectMake(BACKGROUNDX / 2 + 528 + 48 + 48 + 192, BACKGROUNDY - 144 + 48, 144, 48);
}

void mapManager::removeQuestionBlock(int arrNum)
{
	_vQBlock.erase(_vQBlock.begin() + arrNum);
}

void mapManager::removeGoldenBlock()
{
}

void mapManager::removeCoinBlock()
{
}
