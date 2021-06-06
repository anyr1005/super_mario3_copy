#pragma once
#include "gameNode.h"

//block들의 부모 클래스

class block : public gameNode
{
protected:
	image* _imageName;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;

	int _count;

public:
	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	inline RECT getRect() { return _rc; }
};

