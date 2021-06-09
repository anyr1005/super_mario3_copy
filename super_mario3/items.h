#pragma once
#include "gameNode.h"
#include <vector>

enum state
{
	UP,
	LEFT,
	RIGHT,
	FALL
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
	float gravity;
	bool isStop;
};

struct tagItem
{
	image* itemImage; //아이템 이미지
	RECT rc;
	float x, y; // 중점 좌표
	bool isRight; //오른쪽으로 움직일지 왼쪽으로 움직일지
	bool isFired; //발사가 완료 되었는지(블럭에서 완전히 나왔는지 확인)
	bool isOnGround; //땅 위에 있는지 확인
	state state;
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

	const char* _imageName;

public:
	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, bool isRight); //x,y : 아이템 나올 장소, isRight -> 아이템이 오른쪽으로 움직일 지 왼쪽으로 움직일 지 설정
	void move();

	void removeMushroom(int arrNum);

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
	HRESULT init(const char* imageName);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y);

	void move();

	void removeLeaf(int arrNum);

	vector<tagItem> getVMushroom() { return _vLeaf; }
	vector<tagItem>::iterator getViMushroom() { return _viLeaf; }
};