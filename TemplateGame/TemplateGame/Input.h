#pragma once
#include "trace.h"
#include <dinput.h>
#include "GameDefine.h"

class Input
{
private:
	LPDIRECTINPUT8       directInput;		       
	LPDIRECTINPUTDEVICE8 keyboard;	// The keyboard device 
	HWND hwnd;				// Handle of the Game Window
	BYTE  keyStates[256];			// Bộ nhớ đệm --> Mặc định

	// Bộ nhớ đệm lưu dữ liệu input
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];
public:
	Input();
	Input(HINSTANCE hInstance, HWND hwnd);
	~Input();

	void ProcessEscKeyCode();
	int IsKeyDown(int keyCode);

	LPDIRECTINPUTDEVICE8 GetKeyboard();
	LPDIDEVICEOBJECTDATA GetKeyEvents();

};

