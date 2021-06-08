#pragma once
#include "question_block.h"
#include "golden_block.h"
#include "coin_block.h"
#include "gameNode.h"
#include <vector>
class blockManager : public gameNode
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

public :
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setQuestionBlock();
	void setGoldenBlock();
	void setCoinBlock();

	void removeQuestionBlock(int arrNum);
	void removeGoldenBlock(int arrNum);
	void removeCoinBlock(int arrNum);

	vector<block*> getQBlock() { return _vQBlock; }
};

