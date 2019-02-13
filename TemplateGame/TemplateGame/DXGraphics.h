#pragma once
#include "GameDefine.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "trace.h"

class DXGraphics
{
private:
	HINSTANCE hInstance;	// Handle of the game instance
	LPCWSTR nameOfGame;			// Tên của game
	HWND hwnd;
	bool isFullScreen;		// Lựa chọn chế độ màn hình (có fullscreen hay không)
	int screenWidth;
	int screenHeight;
	int frameRate;		// thiết lập số lượng frame được chạy trên 1s
	int mode;				// Chế độ màn hình (640 x 320, ...) 
	int depth;

	// Thiết lập khởi tạo màn hình cho game
	void SetScreenDimension();
	void InitWindow();
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	DXGraphics();
	DXGraphics(HINSTANCE hInstance, LPCWSTR nameOfGame, int mode, int framerate, bool isFullScreen);
	~DXGraphics();

	void SetHInstance(HINSTANCE hInstance);
	void SetNameOfGame(LPCWSTR nameOfGame);
	void SetHwnd(HWND hWnd);
	void SetIsFullScreen(bool isFullScreen);
	void SetScreenHeight(int screenHeight);
	void SetScreenWidth(int screenWidth);
	void SetFrameRate(int frameRate);
	void SetMode(int mode);
	void SetDepth(int depth);

	HINSTANCE GetHInstance();
	LPCWSTR GetNameOfGame();
	HWND GetHwnd();
	bool GetIsFullScreen();
	int GetScreenWidth();
	int GetScreenHeight();
	int GetFrameRate();
	int GetMode();
	int GetDepth();
};

