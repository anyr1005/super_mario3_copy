#include "stdafx.h"
#include "playGround.h"


HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse;

playGround _pg;

void setWindowsSize(int x, int y, int width, int height);

//함수의 프로토 타입 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Application Programming Interface
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int cmdShow)
{
	_hInstance = hInstance;

	//메세지 구조체 : 운영체제에서 발행하는 메시지 정보를 저장하는 구조체
	MSG message;

	//윈도우 정보를 저장하기 위한 구조체
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;	//클래스 여분 메모리
	wndClass.cbWndExtra = 0;	//윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;	//인스턴스 등록
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//윈도우 클래스 정보를 등록해준다
	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		WINNAME,				//윈도우 클래스 이름
		WINNAME,				//윈도우 타이틀 바의 이름
		WS_OVERLAPPEDWINDOW,	//윈도우 스타일
		WINSTARTX,				//윈도우 시작좌표 Left
		WINSTARTY,				//윈도우 시작좌표 top
		WINSIZEX,					//윈도우 가로크기
		WINSIZEY,					//윈도우 세로크기
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//윈도우를 화면에 띄움
	ShowWindow(_hWnd, cmdShow);

	if (FAILED(_pg.init()))
	{
		return NULL;
	}

	//
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	_pg.release();

	UnregisterClass(WINNAME, _hInstance);

	return message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _pg.MainProc(hWnd, iMessage, wParam, lParam);
}


void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;
	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	//실제 클라이언트 영역 조정 들어가는 함수
	AdjustWindowRect(&winRect, WINSTYLE, false);

	//조정된 영역으로 다시 한 번 윈도우 위치 잡아주는 함수
	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}