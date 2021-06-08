#pragma once
#include "gameNode.h"
#include "playerState.h"
#include "mapManager.h"

class playerState;
class mapManager;

class player : public gameNode
{
private:
	image* _img; //�÷��̾� �̹���
	RECT _rc;
	float _x, _y; //���� x, y ��ǥ
	float _runSpeed; //�޸��� �ӵ�
	float _jumpPower; //����

	bool _isRight; //������ ���� ���� ����

	playerState* _state; //����

	mapManager* _mManager;

	bool _isLRCollison;

	bool _isOnGround;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void handleInput();

	void collisonGround();
	void collisonObject();
	void collisonPipe();
	
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

	void setMapManagerMemeoryAddressLink(mapManager* mManager) { _mManager = mManager; }

	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }

	//============================================
	//			## ������ ##

	float getX() { return _x; }
	float getY() { return _y; }

	image* getImage() { return _img; }

	RECT& getRect() { return _rc; }

	float getRunSpeed() { return _runSpeed; }

	bool getIsRight() { return _isRight; }

	bool getIsLRCollison() { return _isLRCollison; }

	bool getIsOnGround() { return _isOnGround; }
	//============================================
};

