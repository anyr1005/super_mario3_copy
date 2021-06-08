#pragma once
#include "gameNode.h"
#include "playerState.h"

class playerState;

class player : public gameNode
{
private:
	image* _img; //�÷��̾� �̹���
	RECT _rc;
	float _x, _y; //���� x, y ��ǥ
	float _runSpeed; //�޸��� �ӵ�
	float _jumpSpeed; //���� �ӵ�

	bool _isRight; //������ ���� ���� ����

	playerState* _state; //����


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void handleInput();

	
	//============================================
	//			## ������ ##

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	void setImage(string imgName)
	{
		_img = IMAGEMANAGER->findImage(imgName);
	}

	void setRunSpeed(float speed) { _runSpeed = speed; }

	void setIsRight(bool b) { _isRight = b; }

	//============================================
	//			## ������ ##

	float getX() { return _x; }
	float getY() { return _y; }

	image* getImage() { return _img; }

	RECT& getRect() { return _rc; }

	float getRunSpeed() { return _runSpeed; }

	bool getIsRight() { return _isRight; }
	//============================================
};

