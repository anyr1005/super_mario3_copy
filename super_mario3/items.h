#pragma once
#include "gameNode.h"
#include <vector>

#define ITEMSPEED 3
//#define GRAVITY 0.1f

enum ItemState
{
	ITEM_UP,
	ITEM_LEFT,
	ITEM_RIGHT,
	ITEM_IDLE
};

struct tagCoin
{
	image* itemImage; //아이템 이미지
	image* effectImage; //이펙트 있는 경우 이펙트 이미지
	RECT rc;
	float x, y; // 중점 좌표
	float fireX, fireY; //처음 좌표
	int count; //프레임 렌더용 함수
	float jumpPower;
	bool isStop;
};

struct tagItem
{
	image* itemImage; //아이템 이미지
	RECT rc;
	float x, y; // 중점 좌표
	float fireX, fireY; //처음 좌표
	float fallSpeed;
	float angle; //각도
	bool isRight;
	bool isOnGround; //땅 위에 있는지 확인
	bool currentFrameY; //나뭇잎 왼쪽 오른쪽 이미지 구분

	ItemState state;
};

class coin : public gameNode
{
private:
	vector<tagCoin> _vCoin;
	vector<tagCoin>::iterator _viCoin;

public:
	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y);

	void move();

	vector<tagCoin> getVCoin() { return _vCoin; }
	vector<tagCoin>::iterator getViCoin() { return _viCoin; }
};

class mushroom : public gameNode
{
private:
	vector<tagItem> _vMushroom;
	vector<tagItem>::iterator _viMushroom;

public:
	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, bool isRight); //x,y : 아이템 나올 장소, isRight -> 아이템이 오른쪽으로 움직일 지 왼쪽으로 움직일 지 설정
	void move();

	void removeMushroom(int arrNum);

	void setIsOnGround(int arrNum, bool b) { _vMushroom[arrNum].isOnGround = b; }

	void setX(int arrNum, float x) { _vMushroom[arrNum].x = x; }
	void setY(int arrNum, float y) { _vMushroom[arrNum].y = y; }
	void setState(int arrNum, ItemState s) { _vMushroom[arrNum].state = s; }

	vector<tagItem> getVMushroom() { return _vMushroom; }
	vector<tagItem>::iterator getViMushroom() { return _viMushroom; }
};

class leaf : public gameNode
{
private:
	vector<tagItem> _vLeaf;
	vector<tagItem>::iterator _viLeaf;

	const char* _imageName;

public:
	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, bool isRight);

	void move();

	void removeLeaf(int arrNum);

	void setIsOnGround(int arrNum, bool b) { _vLeaf[arrNum].isOnGround = b; }

	void setX(int arrNum, float x) { _vLeaf[arrNum].x = x; }
	void setY(int arrNum, float y) { _vLeaf[arrNum].y = y; }
	void setState(int arrNum, ItemState s) { _vLeaf[arrNum].state = s; }

	vector<tagItem> getVLeaf() { return _vLeaf; }
	vector<tagItem>::iterator getViLeaf() { return _viLeaf; }
};