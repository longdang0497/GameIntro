#pragma once
#include "ProcessGame.h"
#include "Graphic.h"
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpStrCmdLine,
	int nShowCmd)
{
	ProcessGame* game = ProcessGame::GetInstance(hInstance, nShowCmd);
	Graphic *graphic = Graphic::GetInstance(NULL, NULL, L"",1);
	// SetWindowPos(graphic->GetHWnd(), 0, 0, 0, graphic->GetWidth() * 2, graphic->GetHeight() * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	game->GameRun();
	return 0;
}