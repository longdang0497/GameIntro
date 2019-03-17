#pragma once
#include "ProcessGame.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpStrCmdLine,
	int nShowCmd)
{
	ProcessGame* game = ProcessGame::GetInstance(hInstance, nShowCmd);
	game->GameRun();
	return 0;
}