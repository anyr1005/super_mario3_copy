#include "stdafx.h"
#include "utils.h"

namespace UTIL
{
	float getDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return sqrtf(x * x + y * y);
	}

	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		//코싸인의 역치역을 구하자      이부분이 코싸인
		float angle = acosf(x / distance);

		//대신에 Y축 보정을 해주자
		if (y2 > y1)
		{
			angle = PI2 - angle;
			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}
}