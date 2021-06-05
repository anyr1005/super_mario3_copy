#pragma once
#include "singletonBase.h"
#include <bitset>	//0과 1 그 비트 입니다

#define KEYMAX 256

using namespace std;

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	keyManager();
	~keyManager();

	HRESULT init();
	void release();

	//키를 누르면
	bool isOnceKeyDown(int key);

	//키를 떼면
	bool isOnceKeyUp(int key);

	//키를 누르고 있으면
	bool isStayKeyDown(int key);

	//키를 토글하면 (캡스락이나 넘락 같은거)
	bool isToggleKey(int key);

	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
};

