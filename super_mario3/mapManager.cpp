#include "stdafx.h"
#include "mapManager.h"

HRESULT mapManager::init()
{
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
	
}

void mapManager::render()
{
	for (_viQBlock = _vQBlock.begin(); _viQBlock != _vQBlock.end(); ++_viQBlock)
	{
		(*_viQBlock)->render();
	}
}

void mapManager::setQuestionBlock()
{
	for (int i = 0; i < 2; i++)
	{
		question_block* qBlock;
		qBlock = new question_block;
		qBlock->init("qBlock", PointMake(552+48*i, BACKGROUNDY - 216));
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
			qBlock->init("qBlock", PointMake(696 + 48 * i, BACKGROUNDY - 359));
		}
		_vQBlock.push_back(qBlock);
		
	}
	
	for (int i = 0; i < 2; i++)
	{
		question_block* qBlock;
		qBlock = new question_block;
		qBlock->init("qBlock", PointMake(1992 + 144 * i, BACKGROUNDY - 120 - 96*i));
		_vQBlock.push_back(qBlock);
	}
	question_block* qBlock;
	qBlock = new question_block;
	qBlock->init("qBlock", PointMake(BACKGROUNDX/2 + 263, BACKGROUNDY - 168));
	_vQBlock.push_back(qBlock);
}
	
void mapManager::setGoldenBlock()
{
}

void mapManager::removeQuestionBlock(int arrNum)
{
	_vQBlock.erase(_vQBlock.begin() + arrNum);
}

void mapManager::removeGoldenBlock()
{
}
