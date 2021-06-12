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
	//����ǥ �ڽ�
	vBlock _vQBlock;
	viBlock _viQBlock;

	//�ݻ��ڽ�
	vBlock _vGBlock;
	viBlock _viGBlock;

	//����
	vBlock _vCoinBlock;
	viBlock _viCoinBlock;

	coin* _coin;
	mushroom* _mushroom;
	leaf* _leaf;

	//item�� �� �浹�� ���� mapManager ����
	mapManager* _mManager;

	bool _isRight; //������ �浹���� ���� �浹����(������ ������ �����̴� ���� ���ؼ�)
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

