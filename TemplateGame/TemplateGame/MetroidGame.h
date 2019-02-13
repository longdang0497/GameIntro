#pragma once
#include "GameDefine.h"
#include "Input.h"
#include <DxErr.h>
#include <Windows.h>
#include "DeviceManager.h"
#include "utils.h"
#include "trace.h"

class MetroidGame
{
protected:
	DWORD deltaTime;	// Thời gian giữa frame hiện tại và frame trước đó đã được vẽ ra
	Input *input;		// Quản lý input
	DXGraphics *dxGraphics;		// Quản lý đồ họa
	DeviceManager *deviceManager;		// Quản lý thiết bị

	void GameRun();

	void CheckKey();
	void RenderFrame();

	void Update(float deltaTime);
	void Render(LPDIRECT3DDEVICE9);
	void LoadResources(LPDIRECT3DDEVICE9);
	void ProcessInput(LPDIRECT3DDEVICE9, float);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);


public:
	MetroidGame();
	MetroidGame(HINSTANCE hInstance, LPCWSTR nameOfGame, int mode, bool isFullScreen, int frameRate);
	~MetroidGame();
};

