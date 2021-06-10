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
	
	//블록 제외 올라갈 수 있는 모든 물체
	vector<RECT> _object;

	//나무블록은 가로막히는것 빼곤 기능이 없으므로 RECT 처리
	vector<RECT> _woodBlock;

	//땅
	vector<RECT> _ground;

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

	vector<RECT> getGround() { return _ground; }

	vector<RECT> getObject() { return _object; }

	vector<tagPipe> getPipe() { return _pipe; }
};

