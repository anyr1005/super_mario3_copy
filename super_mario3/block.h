#pragma once
#include "gameNode.h"

//block���� �θ� Ŭ����

class block : public gameNode
{
protected:
	image* _imageName;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;

	int _count;

	bool _isChange;

	bool _isCrashed;

public:
	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void change();

	inline RECT getRect() { return _rc; }

	inline void setImage(string imgName) { _imageName = IMAGEMANAGER->findImage(imgName); }

	void setIsChange(bool b) { _isChange = b; }

	bool getIsCrashed() { return _isCrashed; }
};

