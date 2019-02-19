#pragma once
#include "GameDefine.h"
#include "Input.h"
#include <DxErr.h>
#include <Windows.h>
#include "DeviceManager.h"
#include "utils.h"
#include "trace.h"
#include "World.h"

// Class này dùng để điều khiển tất cả các thiết bị, xử lý của người dùng và các Object trong thế giới Game
class MetroidGame
{
private:
	DWORD deltaTime;	// Thời gian giữa frame hiện tại và frame trước đó đã được vẽ ra
	Input *input;		// Quản lý input
	DXGraphics *dxGraphics;		// Quản lý đồ họa
	DeviceManager *deviceManager;		// Quản lý thiết bị
	World *world;
	GAME_MODE gameMode;


	void UpdateBelongToGameMode(float deltaTime);
	void UpdateObjects(float deltaTime);
	void RenderBelongToGameMode();
	void RenderFrame();
	void RenderObjects();

	// ----------------- Xử lý sự kiện bàn phím
	void CheckKey();
	void ProcessInput(LPDIRECT3DDEVICE9, float);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
public:
	MetroidGame();
	MetroidGame(HINSTANCE hInstance, LPCWSTR nameOfGame, int mode, bool isFullScreen, int frameRate);
	~MetroidGame();

	void GameRun();

};

