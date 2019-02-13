#include "Input.h"



Input::Input()
{
	this->directInput = NULL;
	this->keyboard = NULL;
	ZeroMemory(this->keyStates, 256);
}

Input::Input(HINSTANCE hInstance, HWND hwnd) {
	this->hwnd = hwnd;

	HRESULT hr = DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&this->directInput,
		NULL);

	if (hr != DI_OK) {
		trace(L"Unable creating DirectInput");
		return;
	}

	hr = this->directInput->CreateDevice(GUID_SysKeyboard, &this->keyboard, NULL);

	if (hr != DI_OK) {
		trace(L"Unable creating DirectInput");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = this->keyboard->SetDataFormat(&c_dfDIKeyboard);

	hr = this->keyboard->SetCooperativeLevel(this->hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; 

	hr = this->keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	hr = this->keyboard->Acquire();

	if (hr != DI_OK) {
		trace(L"Unable creating DirectInput");
		return;
	}

	trace(L"Keyboard has been acquired successfully");
}

Input::~Input()
{
	if (this->directInput != NULL)
		this->directInput->Release();

	if (this->keyboard != NULL)
		this->keyboard->Release();
}

void Input::ProcessEscKeyCode()
{
	HRESULT result;

	// Collect all key states first
	result = this->keyboard->GetDeviceState(sizeof(this->keyStates), this->keyStates);

	if (this->IsKeyDown(DIK_ESCAPE))
	{
		PostMessage(this->hwnd, WM_QUIT, 0, 0);
	}

	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			this->keyboard->Acquire();
		}
	}
}

int Input::IsKeyDown(int keyCode)
{
	return (this->keyStates[keyCode] & 0x80) > 0;
}

// Get/set methods
LPDIRECTINPUTDEVICE8 Input::GetKeyboard()
{
	return this->keyboard;
}

LPDIDEVICEOBJECTDATA Input::GetKeyEvents()
{
	return this->keyEvents;
}
