#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

//멤버 이니셜라이즈
image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0,0,0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //빈 DC영역 생성해줌
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//위에 초기화를 제대로했는데 잘 안됐다면?
	if (_imageInfo == nullptr)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	//DC를 가져다 사용할땐 GetDC()
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//만약에 이미지 초기화가 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	//DC를 가져와서 사용하고 끝에 해제해준다
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	//DC를 가져다 사용할땐 GetDC()
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//만약에 이미지 초기화가 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}


	//DC를 가져와서 사용하고 끝에 해제해준다
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	//DC를 가져다 사용할땐 GetDC()
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//만약에 이미지 초기화가 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}


	//DC를 가져와서 사용하고 끝에 해제해준다
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}


}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}


void image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//복사될 영역의 DC
			_imageInfo->x,		//복사될 좌표(left)
			_imageInfo->y,		//복사될 좌표(top)
			_imageInfo->width,	//복사될 크기 (가로크기)
			_imageInfo->height,	//복사될 크기 (세로크기)
			_imageInfo->hMemDC,	//복사해올 DC 
			0, 0,				//복사해올 시작좌표(left, top)
			_imageInfo->width,	//복사해올 가로크기
			_imageInfo->height,	//복사해올 세로크기
			_transColor			//복사할때 제외할 픽셀값
		);
	}
	else
	{
		//DC영역간의 고속복사
		BitBlt(
			hdc,					//복사할 DC	
			_imageInfo->x,			//복사할 좌표(left)
			_imageInfo->y,			//복사할 좌표(top)
			_imageInfo->width,		//복사할 가로크기
			_imageInfo->height,		//복사할 세로크기
			_imageInfo->hMemDC,		//복사될 DC
			0, 0,					//복사될 시작좌표(left, top)
			SRCCOPY);				//복사할때 변형일으키지말어라~

	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//복사될 영역의 DC
			destX,				//복사될 좌표(left)
			destY,				//복사될 좌표(top)
			_imageInfo->width,	//복사될 크기 (가로크기)
			_imageInfo->height,	//복사될 크기 (세로크기)
			_imageInfo->hMemDC,	//복사해올 DC 
			0, 0,				//복사해올 시작좌표(left, top)
			_imageInfo->width,	//복사해올 가로크기
			_imageInfo->height,	//복사해올 세로크기
			_transColor			//복사할때 제외할 픽셀값
		);
	}
	else
	{
		//DC영역간의 고속복사
		BitBlt(
			hdc,					//복사할 DC	
			destX,					//복사할 좌표(left)
			destY,					//복사할 좌표(top)
			_imageInfo->width,		//복사할 가로크기
			_imageInfo->height,	//복사할 세로크기
			_imageInfo->hMemDC,	//복사될 DC
			0, 0,					//복사될 시작좌표(left, top)
			SRCCOPY);				//복사할때 변형일으키지말어라~

	}

	
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//복사될 영역의 DC
			destX,				//복사될 좌표(left)
			destY,				//복사될 좌표(top)
			sourWidth,			//복사될 크기 (가로크기)
			sourHeight,			//복사될 크기 (세로크기)
			_imageInfo->hMemDC,	//복사해올 DC 
			sourX, sourY,		//복사해올 시작좌표(left, top)
			sourWidth,			//복사해올 가로크기
			sourHeight,			//복사해올 세로크기
			_transColor			//복사할때 제외할 픽셀값
		);
	}
	else
	{
		//DC영역간의 고속복사
		BitBlt(
			hdc,					//복사할 DC	
			destX,					//복사할 좌표(left)
			destY,					//복사할 좌표(top)
			sourWidth,				//복사할 가로크기
			sourHeight,				//복사할 세로크기
			_imageInfo->hMemDC,		//복사될 DC
			sourX, sourY,			//복사될 시작좌표(left, top)
			SRCCOPY);				//복사할때 변형일으키지말어라~

	}

}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//복사될 영역의 DC
			destX,						//복사될 좌표(left)
			destY,						//복사될 좌표(top)
			_imageInfo->frameWidth,		//복사될 크기 (가로크기)
			_imageInfo->frameHeight,	//복사될 크기 (세로크기)
			_imageInfo->hMemDC,			//복사해올 DC 
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,				//복사해올 시작좌표(left, top)
			_imageInfo->frameWidth,		//복사해올 가로크기
			_imageInfo->frameHeight,	//복사해올 세로크기
			_transColor					//복사할때 제외할 픽셀값
		);
	}
	else
	{
		//DC영역간의 고속복사
		BitBlt(
			hdc,					//복사할 DC	
			destX,					//복사할 좌표(left)
			destY,					//복사할 좌표(top)
			_imageInfo->frameWidth,	//복사할 가로크기
			_imageInfo->frameHeight,//복사할 세로크기
			_imageInfo->hMemDC,		//복사될 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//복사될 시작좌표(left, top)
			SRCCOPY);				//복사할때 변형일으키지말어라~

	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//복사될 영역의 DC
			destX,						//복사될 좌표(left)
			destY,						//복사될 좌표(top)
			_imageInfo->frameWidth,		//복사될 크기 (가로크기)
			_imageInfo->frameHeight,	//복사될 크기 (세로크기)
			_imageInfo->hMemDC,			//복사해올 DC 
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,				//복사해올 시작좌표(left, top)
			_imageInfo->frameWidth,		//복사해올 가로크기
			_imageInfo->frameHeight,	//복사해올 세로크기
			_transColor					//복사할때 제외할 픽셀값
		);
	}
	else
	{
		//DC영역간의 고속복사
		BitBlt(
			hdc,					//복사할 DC	
			destX,					//복사할 좌표(left)
			destY,					//복사할 좌표(top)
			_imageInfo->frameWidth,	//복사할 가로크기
			_imageInfo->frameHeight,//복사할 세로크기
			_imageInfo->hMemDC,		//복사될 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//복사될 시작좌표(left, top)
			SRCCOPY);				//복사할때 변형일으키지말어라~

	}
}