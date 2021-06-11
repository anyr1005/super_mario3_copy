#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float angle;
	float speed;
	bool isFire;
	int count;
};

class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);
	void move();

	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }
};

