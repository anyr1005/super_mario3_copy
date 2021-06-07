#pragma once
#include "question_block.h"
#include "golden_block.h"
#include "coin_block.h"
#include "gameNode.h"
#include <vector>

#define GROUNDMAX 6

struct tagPipe
{
	RECT body;
	RECT head;
};

class mapManager : public gameNode
{
private:
	
	//��� ���� �ö� �� �ִ� ��� ��ü
	vector<RECT> _object;

	//��������� ���θ����°� ���� ����� �����Ƿ� RECT ó��
	vector<RECT> _woodBlock;

	//��
	RECT _ground[6];

	vector<tagPipe> _pipe;
	
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setObject();
	void setWoodBlock();
	void setGround();
	void setPipe();
};

