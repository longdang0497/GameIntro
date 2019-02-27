#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <iostream>
#include "trace.h"
#include "MetroidGame.h"

using namespace std;

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpStrCmdLine,
	int nShowCmd)
{
	clearFile();
	MetroidGame* metroidGame = new MetroidGame(hInstance, DEFAULT_NAME_OF_GAME, DEFAULT_SCREEN_MODE, false, DEFAULT_FRAME_RATE);
	metroidGame->GameRun();
	return 0;
}