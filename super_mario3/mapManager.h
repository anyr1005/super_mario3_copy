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
	vBlock _vQBlock;
	viBlock _viQBlock;
	vBlock _vGBlock;
	viBlock _viGBlock;
	vBlock _vCoinBlock;
	viBlock _viCoinBlock;
	RECT _object[OBJECTMAX];

	//나무블록은 가로막히는것 빼곤 기능이 없으므로 RECT 처리
	RECT _wood_block[WOODBLOCKMAX];
	
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setQuestionBlock();
	void setGoldenBlock();
	void setCoinBlock();
	void setObject();


	void removeQuestionBlock(int arrNum);
	void removeGoldenBlock();
	void removeCoinBlock();
};

