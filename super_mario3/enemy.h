#pragma once
#include "gameNode.h"

#define ENEMYSPEED 3

//enemy는 jump인지 walk인지에 따라 이미지만 다르게 주면 됨
enum EnemyState
{
	LEFT_WALK,
	RIGHT_WALK,
	LEFT_JUMP,
	RIGHT_JUMP,
	IDLE,
	DIE
};

class enemy : public gameNode
{
protected:
	image* _image;
	RECT _rc;

	float _x, _y; //현재 enemy 좌표
	float _spawnX, _spawnY; //enemy 스폰 좌표

	int _currentFrameX;
	int _currentFrameY;

	int _count;

	float _jumpPower;

	bool _isOnGround;

	EnemyState _state;

public:
	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	inline RECT getRect() { return _rc; }

	virtual void move() {};
	virtual void draw() {};

};

