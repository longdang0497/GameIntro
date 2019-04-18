#include "Graphic.h"

Graphic* Graphic::_instance = NULL;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void Graphic::SetDimension(int mode) {
	switch (mode)
	{
	case GAME_MODE_320_240:
		this->screenWidth = 320;
		this->screenHeight = 240;
		break;
	case GAME_MODE_640_480:
		this->screenWidth = 640;
		this->screenHeight = 480;
		break;
	case GAME_MODE_256_256:
		this->screenWidth = 256;
		this->screenHeight = 293;
		break;
	default:
		this->screenWidth = 300;
		this->screenHeight = 300;
		break;
	}
}

Graphic::Graphic(HINSTANCE hInstance, int nShowCmd, LPCWSTR nameOfGame, int gameMode)
{
	this->SetDimension(gameMode);

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = nameOfGame;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	this->hWnd =
		CreateWindow(
			nameOfGame,
			nameOfGame,
			WS_OVERLAPPEDWINDOW, 
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			this->screenWidth,
			this->screenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return;
	}

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);
}


Graphic::~Graphic()
{
}
