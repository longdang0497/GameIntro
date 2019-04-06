#pragma once
#include <Windows.h>
#include "Define.h"
class Graphic
{
private:

	static Graphic* _instance;

	HINSTANCE hInstance;	// Handle of the game instance
	LPCWSTR nameOfGame;			// Tên của game
	HWND hWnd;

	int screenWidth;
	int screenHeight;

	void SetDimension(int);

public:
	Graphic(HINSTANCE hInstance, int nShowCmd, LPCWSTR nameOfGame, int gameMode);
	~Graphic();

	HWND GetHWnd() { return this->hWnd; }
	int GetWidth() { return this->screenWidth; }
	int GetHeight() { return this->screenHeight; }
	static Graphic* GetInstance(HINSTANCE hInstance, int nShowCmd, LPCWSTR nameOfGame, int gameMode) {
		if (_instance == NULL) _instance = new Graphic(hInstance, nShowCmd, nameOfGame, gameMode);
		return _instance;
	};
};

