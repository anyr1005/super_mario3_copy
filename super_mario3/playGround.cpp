#include "stdafx.h"
#include "playGround.h"

//�ʱ�ȭ
HRESULT playGround::init()
{
	gameNode::init(true);

	
	return S_OK;
}

//�޸� ����
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();

	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================


	//==================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
