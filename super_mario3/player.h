#pragma once
#include "gameNode.h"
#include "playerState.h"
#include "mapManager.h"
#include "blockManager.h"

class playerState;
class mapManager;
class blockManager;

enum PlayerShape
{
	BASIC,
	SUPER,
	TAIL
};

class player : public gameNode
{
private:
	image* _img; //플레이어 이미지
	RECT _rc;
	RECT _collisonRange;

	float _x, _y; //중점 x, y 좌표
	float _runSpeed; //달리는 속도
	float _jumpPower; //점프

	bool _isRight; //오른쪽 왼쪽 방향 구분

	playerState* _state; //상태

	PlayerShape _shape;

	mapManager* _mManager;

	blockManager* _bManager;

	bool _isLRCollison; //오른쪽이나 왼쪽으로 부딪혔는지

	bool _isOnGround; //땅에 있는지

	bool _isAttacked;
	int _attackedCount;

	int _alphaValue; //enemy에게 맞을 경우 깜박거리는 효과 위해서

	int _flyCount;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void handleInput();

	void collisonGround();
	void collisonObject();
	void collisonPipe();
	void collisonWoodBlock();

	void collisonQBlock();
	void collisonGBlock();
	void collisonCoinBlock();

	void collisonMushroom();
	void collisonLeaf();

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

	void setMapManagerMemeoryAddressLink(mapManager* mManager) { _mManager = mManager; }

	void setBlockManagerMemoryAddressLink(blockManager* blockManager) { _bManager = blockManager; }

	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }

	void setPlayerShape(PlayerShape p) { _shape = p; }

	//============================================
	//			## 접근자 ##

	float getX() { return _x; }
	float getY() { return _y; }

	image* getImage() { return _img; }

	RECT& getRect() { return _rc; }
	RECT getCollisonRange() { return _collisonRange; }

	float getRunSpeed() { return _runSpeed; }

	bool getIsRight() { return _isRight; }

	bool getIsLRCollison() { return _isLRCollison; }

	bool getIsOnGround() { return _isOnGround; }

	PlayerShape getPlayerShape() { return _shape; }

	playerState* getPlayerState() { return _state; }

	void setPlayerState(playerState* state) { _state = state; }

	bool getIsAttacked() { return _isAttacked; }
	void setIsAttacked(bool b) { _isAttacked = b; }

	int getFlyCount() { return _flyCount; }
	void setFlyCount(int i) { _flyCount = i; }
	//============================================
};

