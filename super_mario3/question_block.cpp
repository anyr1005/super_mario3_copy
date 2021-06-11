#include "stdafx.h"
#include "question_block.h"

void question_block::change()
{
	_imageName = IMAGEMANAGER->findImage("q_change");

	_currentFrameX = 0;
	_currentFrameY = 0;

	_changeCount++;
	if (_changeCount % 2 == 0)
	{
		if (_countMove < 7)
		{
			_rc.top -= 5;
			_rc.bottom -= 5;
		}
		else if (_countMove < 14)
		{
			_rc.top += 5;
			_rc.bottom += 5;
		}
		else
		{
			_imageName = IMAGEMANAGER->findImage("q_change_complete");
			_isChange = false;
			_isCrashed = true;
		}
		_countMove++;
		_changeCount = 0;
	}
}
