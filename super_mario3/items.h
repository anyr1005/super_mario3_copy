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
	image* itemImage; //������ �̹���
	image* effectImage; //����Ʈ �ִ� ��� ����Ʈ �̹���
	RECT rc;
	float x, y; // ���� ��ǥ
	float fireX, fireY; //ó�� ��ǥ
	int count; //������ ������ �Լ�
	float jumpPower;
	bool isStop;
};

struct tagItem
{
	image* itemImage; //������ �̹���
	RECT rc;
	float x, y; // ���� ��ǥ
	float fireX, fireY; //ó�� ��ǥ
	float fallSpeed;
	float angle; //����
	bool isRight;
	bool isOnGround; //�� ���� �ִ��� Ȯ��
	bool currentFrameY; //������ ���� ������ �̹��� ����

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

	void fire(float x, float y, bool isRight); //x,y : ������ ���� ���, isRight -> �������� ���������� ������ �� �������� ������ �� ����
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