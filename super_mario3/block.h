#pragma once
#include "gameNode.h"

//block들의 부모 클래스

enum item
{
	COIN,
	MUSHROOM,
	LEAF,
	LIFE,
	SWITCH,
	PARTICLE
};

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
	
	bool _isFire;

	item _item;

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

	void setIsFire(bool b) { _isFire = b; }

	void setItem(item i) { _item = i; }

	bool getIsCrashed() { return _isCrashed; }

	bool getIsFire() { return _isFire; }

	item getItem() { return _item; }
};

