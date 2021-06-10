#pragma once
#include "gameNode.h"
#include <vector>

#define ITEMSPEED 5
#define GRAVITY 0.1f

enum state
{
	UP,
	LEFT,
	RIGHT
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
	bool isOnGround; //�� ���� �ִ��� Ȯ��
	float fallPower;
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

	void fire(float x, float y, bool isRight); //x,y : ������ ���� ���, isRight -> �������� ���������� ������ �� �������� ������ �� ����
	void move();

	void removeMushroom(int arrNum);

	void setIsOnGround(int arrNum, bool b) { _vMushroom[arrNum].isOnGround = b; }

	void setX(int arrNum, float x) { _vMushroom[arrNum].x = x; }
	void setY(int arrNum, float y) { _vMushroom[arrNum].y = y; }
	void setState(int arrNum, state s) { _vMushroom[arrNum].state = s; }

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