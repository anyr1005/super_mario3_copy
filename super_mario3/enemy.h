#pragma once
#include "gameNode.h"

#define ENEMYSPEED 4

//enemy�� jump���� walk������ ���� �̹����� �ٸ��� �ָ� ��
enum EnemyState
{
	ENEMY_LEFT_WALK, //UP WALK�ε� ����(���� �ö��)
	ENEMY_RIGHT_WALK, //DOWN WALK�ε� ����(���� �ö��)
	ENEMY_LEFT_JUMP,
	ENEMY_RIGHT_JUMP,
	ENEMY_IDLE,
	ENEMY_DIE, //���� �������� �׾��� ��
	ENEMY_ATTACKED //������ ����� �׾��� ��
};

class enemy : public gameNode
{
protected:
	image* _image;
	RECT _rc;

	float _x, _y; //���� enemy ��ǥ
	float _spawnX, _spawnY; //enemy ���� ��ǥ

	int _currentFrameX;
	int _currentFrameY;

	int _count; //�����ӿ� ī��Ʈ
	int _deadCount; //�׾��� �� �ٽ� ��������� ī��Ʈ

	float _jumpPower;

	bool _isOnGround; //�� ���� �ִ��� Ȯ��

	RECT _collisonRange; //�浹 ���� ��Ʈ

	bool _isShell; //���ݾ��� ���°� �������

	bool _isVisible; //���� ���¿��� ������ �ʰ� �Ұ���

	EnemyState _state;

	EnemyState _firstState; //�ʱ� ����

public:
	virtual HRESULT init();
	virtual HRESULT init(EnemyState es ,POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	inline RECT getRect() { return _rc; }

	virtual void move() {}; //���ʹ� ������
	virtual void draw() {};

	virtual bool bulletCountFire() { return false;  };

	RECT getCollisonRange() { return _collisonRange; }

	float getX() { return _x; }
	float getY() { return _y; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	EnemyState getState() { return _state; }

	void setState(EnemyState es) { _state = es; } //���ʹ� ���� set
	void setImage(string s) { _image = IMAGEMANAGER->findImage(s); }

	void setIsShell(bool b) { _isShell = b; }
	bool getIsShell() { return _isShell; }

	void setIsVisible(bool b) { _isVisible = b; }
	bool getIsVisible() { return _isVisible; }

	void setIsOnGround(bool b) { _isOnGround = b; }

	void setJumpPower(float f) { _jumpPower = f; }
};

