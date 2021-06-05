#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", BACKGROUNDX, BACKGROUNDY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit; //매니저를 포함하는지 여부
	
public:
	
	virtual HRESULT init();			//초기화 함수
	virtual HRESULT init(bool managerInit);
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 함수
	virtual void render();			//그리기 함수

	image* getBackBuffer() { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

