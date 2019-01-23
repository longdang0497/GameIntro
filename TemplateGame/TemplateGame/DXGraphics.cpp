#include "DXGraphics.h"



DXGraphics::DXGraphics()
{
	
}

DXGraphics::DXGraphics(HINSTANCE hInstance, LPCWSTR nameOfGame = DEFAULT_NAME_OF_GAME, int mode = DEFAULT_SCREEN_MODE,
	int framerate = DEFAULT_FRAME_RATE, bool isFullScreen = DEFAULT_IS_FULL_SCREEN) {

	this->hInstance = hInstance;
	this->nameOfGame = nameOfGame;
	this->mode = mode;
	this->frameRate = frameRate;
	this->isFullScreen = isFullScreen;
	this->SetScreenDimension();
	this->InitWindow();
}

DXGraphics::~DXGraphics()
{

}

void DXGraphics::SetScreenDimension() {

	switch (this->mode) {
	case GAME_SCREEN_RESOLUTION_640_480_24:
		this->screenWidth = 640;
		this->screenHeight = 480;
		this->depth = 24;
		break;

	case GAME_SCREEN_RESOLUTION_800_600_24:
		this->screenWidth = 800;
		this->screenHeight = 600;
		this->depth = 24;
		break;

	case GAME_SCREEN_RESOLUTION_1024_768_24:
		this->screenWidth = 1024;
		this->screenHeight = 768;
		this->depth = 24;
		break;

	default:
		trace(L"Unable setting screen's dimension");
	}


}

void DXGraphics::InitWindow() {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = this->hInstance;

	wc.lpfnWndProc = (WNDPROC)DXGraphics::WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->nameOfGame;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	DWORD style;
	if (this->isFullScreen)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	this->hwnd =
		CreateWindow(
			this->nameOfGame,
			this->nameOfGame,
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			this->screenWidth,
			this->screenHeight,
			NULL,
			NULL,
			this->hInstance,
			NULL);

	if (!this->hwnd)
	{
		MessageBox(this->hwnd, L"[ERROR] Failed to created window!", NULL, NULL);
	}

	ShowWindow(this->hwnd, SW_SHOWNORMAL);
	UpdateWindow(this->hwnd);
}

// Mặc định
LRESULT DXGraphics::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Process message sent to windows
	switch (message) {
	case WM_ACTIVATE:
		if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE) {
			PostMessage(hWnd, WM_ACTIVATE, wParam, lParam);
		}
		break;
	case WM_CLOSE: // Windows is about to be closed because user click Close button or press Alt + F4
		break;
	case WM_DESTROY: // Windows is already closed and is about to be destroyed
		PostQuitMessage(0); // put quit message to message queue
		break;
	default:
		break;
	}

	// Default message behaviors
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// Get/set Methods
void DXGraphics::setHInstance(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
}

void DXGraphics::setNameOfGame(LPCWSTR nameOfGame)
{
	this->nameOfGame = nameOfGame;
}

void DXGraphics::setHwnd(HWND hWnd)
{
	this->hwnd = hwnd;
}

void DXGraphics::setIsFullScreen(bool isFullScreen)
{
	this->isFullScreen = isFullScreen;
}

void DXGraphics::setScreenHeight(int screenHeight)
{
	this->screenHeight = screenHeight;
}

void DXGraphics::setScreenWidth(int screenWidth)
{
	this->screenWidth = screenWidth;
}

void DXGraphics::setFrameRate(int frameRate)
{
	this->frameRate = frameRate;
}

void DXGraphics::setMode(int mode)
{
	this->mode = mode;
}

void DXGraphics::setDepth(int depth)
{
	this->depth = depth;
}

HINSTANCE DXGraphics::getHInstance()
{
	return this->hInstance;
}

LPCWSTR DXGraphics::getNameOfGame()
{
	return this->nameOfGame;
}

HWND DXGraphics::getHwnd()
{
	return this->hwnd;
}

bool DXGraphics::getIsFullScreen()
{
	return this->isFullScreen;
}

int DXGraphics::getScreenWidth()
{
	return this->screenWidth;
}

int DXGraphics::getScreenHeight()
{
	return this->screenHeight;
}

int DXGraphics::getFrameRate()
{
	return this->frameRate;
}

int DXGraphics::getMode()
{
	return this->mode;
}

int DXGraphics::getDepth()
{
	return this->depth;
}
