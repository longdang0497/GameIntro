#pragma once
#include <dinput.h>
#include <dinput.h>

class CKeyBoard
{
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	LPDIRECTINPUT8       m_di;
	LPDIRECTINPUTDEVICE8 m_keyboard;
	DIDEVICEOBJECTDATA m_keyEvents[256];
	bool pressed[256];
	BYTE  m_keyStates[256];
	CKeyBoard(HINSTANCE hInstance, HWND hWnd);

	static CKeyBoard* instance;
public:
	static CKeyBoard* getInstance();

	static void Create(HINSTANCE hInstance, HWND hWnd);
	void UpdateKeyboard();
	void PollKeyboard();
	bool IsKeyDown(BYTE keyCode);
	bool IsKeyUp(BYTE keyCode);
	void Release();
	CKeyBoard();
	~CKeyBoard();
};

