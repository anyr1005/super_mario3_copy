#pragma once
#include "question_block.h"
#include "golden_block.h"
#include "coin_block.h"
#include "gameNode.h"
#include "items.h"
#include "mapManager.h"
#include <vector>

class mapManager;

class blockManager : public gameNode
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

	coin* _coin;
	mushroom* _mushroom;
	leaf* _leaf;

	//item과 땅 충돌을 위해 mapManager 참조
	mapManager* _mManager;

	bool _isRight; //오른쪽 충돌인지 왼쪽 충돌인지(버섯과 나뭇잎 움직이는 방향 위해서)
	bool _isLeaf;


public :
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void removeQuestionBlock(int arrNum);
	void removeGoldenBlock(int arrNum);
	void removeCoinBlock(int arrNum);

	void mushroomCollision();
	void leafCollision();

	void setQuestionBlock();
	void setGoldenBlock();
	void setCoinBlock();

	void setMapManagerMemeoryAddressLink(mapManager* mManager) { _mManager = mManager; }

	vector<block*> getQBlock() { return _vQBlock; }
	vector<block*> getGBlock() { return _vGBlock; }

	coin* getCoin() { return _coin; }
	mushroom* getMushroom() { return _mushroom; }
	leaf* getLeaf() { return _leaf; }

	void setIsRight(bool b) { _isRight = b; }

	void setIsLeaf(bool b) { _isLeaf = b; }
};

