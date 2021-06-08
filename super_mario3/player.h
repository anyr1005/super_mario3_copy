#pragma once
#include "gameNode.h"
#include "playerState.h"

class playerState;

class player : public gameNode
{
private:
	image* _img; //플레이어 이미지
	RECT _rc;
	float _x, _y; //중점 x, y 좌표
	float _runSpeed; //달리는 속도
	float _jumpSpeed; //점프 속도

	bool _isRight; //오른쪽 왼쪽 방향 구분

	playerState* _state; //상태


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void handleInput();

	
	//============================================
	//			## 설정자 ##

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	void setImage(string imgName)
	{
		_img = IMAGEMANAGER->findImage(imgName);
	}

	void setRunSpeed(float speed) { _runSpeed = speed; }

	void setIsRight(bool b) { _isRight = b; }

	//============================================
	//			## 접근자 ##

	float getX() { return _x; }
	float getY() { return _y; }

	image* getImage() { return _img; }

	RECT& getRect() { return _rc; }

	float getRunSpeed() { return _runSpeed; }

	bool getIsRight() { return _isRight; }
	//============================================
};

