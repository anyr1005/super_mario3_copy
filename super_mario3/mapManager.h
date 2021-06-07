#pragma once
#include "question_block.h"
#include "golden_block.h"
#include "coin_block.h"
#include "gameNode.h"
#include <vector>

#define OBJECTMAX 14
#define WOODBLOCKMAX 7

class mapManager : public gameNode
{
private:
	typedef vector<block*> vBlock;
	typedef vector<block*>::iterator viBlock;

private:
	//����ǥ �ڽ�
	vBlock _vQBlock;
	viBlock _viQBlock;
	
	//�ݻ��ڽ�
	vBlock _vGBlock;
	viBlock _viGBlock;
	
	//����
	vBlock _vCoinBlock;
	viBlock _viCoinBlock;

	//��� ���� �ö� �� �ִ� ��� ��ü
	vector<RECT> _object;

	//��������� ���θ����°� ���� ����� �����Ƿ� RECT ó��
	vector<RECT> _woodBlock;
	
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setQuestionBlock();
	void setGoldenBlock();
	void setCoinBlock();
	void setObject();
	void setWoodBlock();

	void removeQuestionBlock(int arrNum);
	void removeGoldenBlock();
	void removeCoinBlock();
};

