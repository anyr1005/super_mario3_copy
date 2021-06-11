#pragma once
#include "gameNode.h"

#define ENEMYSPEED 4

//enemy는 jump인지 walk인지에 따라 이미지만 다르게 주면 됨
enum EnemyState
{
	ENEMY_LEFT_WALK, //UP WALK로도 쓰임(뻐끔 플라워)
	ENEMY_RIGHT_WALK, //DOWN WALK로도 쓰임(뻐끔 플라워)
	ENEMY_LEFT_JUMP,
	ENEMY_RIGHT_JUMP,
	ENEMY_IDLE,
	ENEMY_DIE, //점프 공격으로 죽었을 때
	ENEMY_ATTACKED //꼬리나 등껍질로 죽었을 때
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

	int _count; //프레임용 카운트
	int _deadCount; //죽었을 때 다시 나오기까지 카운트

	float _jumpPower;

	bool _isOnGround; //땅 위에 있는지 확인

	RECT _collisonRange; //충돌 범위 렉트

	bool _isShell; //엉금엉금 상태가 등껍질인지

	bool _isVisible; //죽은 상태여서 보이지 않게 할건지

	EnemyState _state;

	EnemyState _firstState; //초기 상태

public:
	virtual HRESULT init();
	virtual HRESULT init(EnemyState es ,POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	inline RECT getRect() { return _rc; }

	virtual void move() {}; //에너미 움직임
	virtual void draw() {};

	virtual bool bulletCountFire() { return false;  };

	RECT getCollisonRange() { return _collisonRange; }

	float getX() { return _x; }
	float getY() { return _y; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	EnemyState getState() { return _state; }

	void setState(EnemyState es) { _state = es; } //에너미 상태 set
	void setImage(string s) { _image = IMAGEMANAGER->findImage(s); }

	void setIsShell(bool b) { _isShell = b; }
	bool getIsShell() { return _isShell; }

	void setIsVisible(bool b) { _isVisible = b; }
	bool getIsVisible() { return _isVisible; }

	void setIsOnGround(bool b) { _isOnGround = b; }

	void setJumpPower(float f) { _jumpPower = f; }
};

