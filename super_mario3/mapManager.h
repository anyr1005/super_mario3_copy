#pragma once
#include "qBlock.h"
#include "gameNode.h"
#include <vector>

class mapManager : public gameNode
{
private:
	typedef vector<block*> vBlock;
	typedef vector<block*>::iterator viBlock;

private:
	vBlock _vQBlock;
	viBlock _viQBlock;
	
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setQuestionBlock();
	void setGoldenBlock();

	void removeQuestionBlock(int arrNum);
	void removeGoldenBlock();

};

