#include "stdafx.h"
#include "mapManager.h"

HRESULT mapManager::init()
{
	setQuestionBlock();
	setGoldenBlock();
	setCoinBlock();
	setObject();
	setWoodBlock();
	setGround();
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
		for (int i = 0; i < _object.size(); i++)
		{
			Rectangle(getMemDC(), _object[i]);
		}
		for (int i = 0; i < _woodBlock.size(); i++)
		{
			Rectangle(getMemDC(), _woodBlock[i]);
		}
		for (int i = 0; i < GROUNDMAX; i++)
		{
			Rectangle(getMemDC(), _ground[i]);
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
	for (int i = 0; i < 2; i++)
	{
		_object.push_back(RectMake(720 + 96 * i, BACKGROUNDY - 192 - 96 * i, 144, 30));
	}

	for (int i = 0; i < 2; i++)
	{
		_object.push_back(RectMake(1200 + 192 * i, BACKGROUNDY - 192 - 96 * i, 240 - 48 * i, 30));
	}
	for (int i = 0; i < 2; i++)
	{
		_object.push_back(RectMake(1536, BACKGROUNDY - 384 + 240 * i, 192 + 96 * i, 30));
	}

	for (int i = 0; i < 3; i++)
	{
		_object.push_back(RectMake(BACKGROUNDX / 2 - 384 + 96 * i, BACKGROUNDY - 144 - 96 * i , 336, 30));
	}

	for (int i = 0; i < 2; i++)
	{
		_object.push_back(RectMake(BACKGROUNDX - 2016 + 96 * i, BACKGROUNDY - 192 - 288 * i, 144, 30));
	}

	//하늘에 있는 부유물
	_object.push_back(RectMake(BACKGROUNDX / 2 - 240, 432, 192, 30));

	//구름
	_object.push_back(RectMake(BACKGROUNDX / 2 + 48, 576, 192, 48));
	_object.push_back(RectMake(BACKGROUNDX / 2 + 288, 528, 624, 48));

}

void mapManager::setWoodBlock()
{
	_woodBlock.push_back(RectMake(BACKGROUNDX / 2 + 336, BACKGROUNDY - 288, 96, 48));
	for (int i = 0; i < 3; i++)
	{
		_woodBlock.push_back(RectMake(BACKGROUNDX / 2 + 528 + (48 * i), BACKGROUNDY - 96 - (48 * i), 144 - 48 * i, 48));
	}
	for (int i = 0; i < 3; i++)
	{
		_woodBlock.push_back(RectMake(BACKGROUNDX / 2 + 816, BACKGROUNDY - 96 - (48 * i), 144 - 48 * i, 48));
	}
}

void mapManager::setGround()
{
	_ground[0] = RectMake(0, BACKGROUNDY - 48, 1872, 48);
	_ground[1] = RectMake(_ground[0].right, BACKGROUNDY - 96, 1392, 96);
	_ground[2] = RectMake(BACKGROUNDX / 2 - 720, BACKGROUNDY - 48, 1056, 48);
	_ground[3] = RectMake(BACKGROUNDX / 2 + 432, BACKGROUNDY - 48, 240, 48);
	_ground[4] = RectMake(BACKGROUNDX / 2 + 816, BACKGROUNDY - 48, 1632, 48);
	_ground[5] = RectMake(BACKGROUNDX - 1680, BACKGROUNDY - 48, 1680, 48);
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
