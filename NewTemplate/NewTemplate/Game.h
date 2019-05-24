#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Input.h"
#include "Debug.h"
#include "Texture.h"
#include "Sprite.h"
#include "Define.h"
#include "KeyBoard.h"

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024
#define MAX_FRAME_RATE 120

class Game
{
private: 
	static Game * _instance;

	GAME_STAGE gameStage;

	HWND hWnd;

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	Input * keyHandler;
	

public:
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right,int bottom, int alpha = 255);
	
	// Khởi tạo bàn phím
	void InitKeyboard(Input*);
	int IsKeyDown(int keyCode);
	void ProcessKeyboard();

	// Các hàm Get/set
	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetGameStage(GAME_STAGE gameStage) { this->gameStage = gameStage; }
	GAME_STAGE GetGameStage() { return this->gameStage; }
	

	static Game * GetInstance() {
		if (_instance == NULL) _instance = new Game();
		return _instance;
	};

	HWND GetHWnd() { return this->hWnd; }

	~Game();

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float &t,
		float &nx,
		float &ny);

	static bool IsIntersect(RECT rectA, RECT rectB);


};

