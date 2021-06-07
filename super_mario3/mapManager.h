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
	//물음표 박스
	vBlock _vQBlock;
	viBlock _viQBlock;
	
	//금색박스
	vBlock _vGBlock;
	viBlock _viGBlock;
	
	//코인
	vBlock _vCoinBlock;
	viBlock _viCoinBlock;

	//블록 제외 올라갈 수 있는 모든 물체
	vector<RECT> _object;

	//나무블록은 가로막히는것 빼곤 기능이 없으므로 RECT 처리
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

