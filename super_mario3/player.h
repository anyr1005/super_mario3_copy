#pragma once
#include "gameNode.h"
#include "playerState.h"

class playerState;

#define BASICSPEED 5
#define SPEEDMAX 12
#define ACCEL 0.1f
#define FRICTION 0.2f

class player : public gameNode
{
private:
	image* _img;
	RECT _rc;
	float _x, _y;
	float _runSpeed;
	float _jumpSpeed;
	float _friction;
	int _count, _index;

	playerState* _state;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void handleInput();

	float getX() { return _x; }
	float getY() { return _y; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	void setImage(string imgName)
	{
		_img = IMAGEMANAGER->findImage(imgName);
	}

	image* getImage() { return _img; }

	RECT& getRect() { return _rc; }

	float getRunSpeed() { return _runSpeed; }

	void setRunSpeed(float speed) { _runSpeed = speed; }
};

