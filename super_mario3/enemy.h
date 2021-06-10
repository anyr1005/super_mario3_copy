#pragma once
#include "gameNode.h"

class enemy : public gameNode
{
protected:
	image* _image;
	RECT _rc;

	float _x, _y;

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

