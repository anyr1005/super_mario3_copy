#pragma once
#include "block.h"
class question_block : public block
{
private:
	int _changeCount = 0;
	int _countMove = 0;
public:
	virtual void change();
};

