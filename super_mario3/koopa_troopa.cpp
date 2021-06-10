#include "stdafx.h"
#include "koopa_troopa.h"

HRESULT koopa_troopa::init(const char * imageName, POINT position)
{
	return E_NOTIMPL;
}

void koopa_troopa::move()
{
	switch (_state)
	{
	case LEFT_WALK:
		break;
	case RIGHT_WALK:
		break;
	case LEFT_JUMP:
		break;
	case RIGHT_JUMP:
		break;
	case IDLE:
		break;
	default:
		break;
	}
}

void koopa_troopa::draw()
{

}
