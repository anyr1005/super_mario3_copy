#include "stdafx.h"
#include "mapManager.h"

HRESULT mapManager::init()
{
	IMAGEMANAGER->addImage("pipe_head", "img/pipe_head.bmp", 96, 48, true, RGB(255, 0, 255), FALSE);

	setObject();
	setWoodBlock();
	setGround();
	setPipe();
	return S_OK;
}

void mapManager::release()
{
}

void mapManager::update()
{

}

void mapManager::render()
{
	for (int i = 0; i < _pipe.size()-1; i++)
	{
		IMAGEMANAGER->findImage("pipe_head")->render(getMemDC(), _pipe[i].head.left, _pipe[i].head.top);
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
		for (int i = 0; i < _pipe.size(); i++)
		{
			Rectangle(getMemDC(), _pipe[i].head);
			Rectangle(getMemDC(), _pipe[i].body);
		}
	}
}

void mapManager::setObject()
{
	for (int i = 0; i < 2; i++)
	{
		_object.push_back(RectMake(720 + 96 * i, BACKGROUNDY - 192 - 96 * i, 144, 10));
	}

	for (int i = 0; i < 2; i++)
	{
		_object.push_back(RectMake(1200 + 192 * i, BACKGROUNDY - 192 - 96 * i, 240 - 48 * i, 10));
	}
	for (int i = 0; i < 2; i++)
	{
		_object.push_back(RectMake(1536, BACKGROUNDY - 384 + 240 * i, 192 + 96 * i, 10));
	}

	for (int i = 0; i < 3; i++)
	{
		_object.push_back(RectMake(BACKGROUNDX / 2 - 384 + 96 * i, BACKGROUNDY - 144 - 96 * i, 336, 10));
	}

	for (int i = 0; i < 2; i++)
	{
		_object.push_back(RectMake(BACKGROUNDX - 2016 + 96 * i, BACKGROUNDY - 192 - 288 * i, 144, 10));
	}

	//하늘에 있는 부유물
	_object.push_back(RectMake(BACKGROUNDX / 2 - 240, 432, 192, 10));
	
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
	for (int i = 0; i < 2; i++)
	{
		_woodBlock.push_back(RectMake(BACKGROUNDX - 1680, BACKGROUNDY - 192 * (i + 1), 96, 48));
	}
}

void mapManager::setGround()
{
	_ground.push_back(RectMake(0, BACKGROUNDY - 48, 1872, 48));
	_ground.push_back(RectMake(_ground[0].right, BACKGROUNDY - 96, 1392, 96));
	_ground.push_back(RectMake(BACKGROUNDX / 2 - 720, BACKGROUNDY - 48, 1056, 48));
	_ground.push_back(RectMake(BACKGROUNDX / 2 + 432, BACKGROUNDY - 48, 240, 48));
	_ground.push_back(RectMake(BACKGROUNDX / 2 + 816, BACKGROUNDY - 48, 1632, 48));
	_ground.push_back(RectMake(BACKGROUNDX - 1680, BACKGROUNDY - 48, 1680, 48));
}

void mapManager::setPipe()
{
	tagPipe pipe;
	pipe.head = RectMake(1056, BACKGROUNDY - 192, 96, 48);
	pipe.body = RectMake(1059, BACKGROUNDY - 144, 90, 96);
	_pipe.push_back(pipe);

	for (int i = 0; i < 2; i++)
	{
		pipe.head = RectMake(BACKGROUNDX / 2 + 1104 + 192 * i, BACKGROUNDY - 144 - 48 * i, 96, 48);
		pipe.body = RectMake(BACKGROUNDX / 2 + 1107 + 192 * i, BACKGROUNDY - 96 - 48 * i, 90, 48 + 48 * i);
		_pipe.push_back(pipe);
	}
	
	pipe.head = RectMake(BACKGROUNDX - 1680, 336, 96, 48);
	pipe.body = RectMake(BACKGROUNDX - 1677, 384, 90, 528);
	_pipe.push_back(pipe);
	
	pipe.head = RectMake(BACKGROUNDX - 1488, BACKGROUNDY - 144, 96, 48);
	pipe.body = RectMake(BACKGROUNDX - 1485, BACKGROUNDY - 96, 90, 48);
	_pipe.push_back(pipe);

	//파이프 몸통만 있는 것 head와 body를 같게 해서 넣어줌
	pipe.body = RectMake(BACKGROUNDX - 1677, BACKGROUNDY - 144, 90, 96);
	pipe.head = RectMake(BACKGROUNDX - 1677, BACKGROUNDY - 144, 90, 96);
	_pipe.push_back(pipe);
}
