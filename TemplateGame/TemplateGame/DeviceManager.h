#pragma once
#include "DXGraphics.h"
#include <time.h>
class DeviceManager
{
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddv;		// Dùng để render
	LPDIRECT3DSURFACE9 backBuffer;	// con trỏ hướng tới backbuffer
	LPDIRECT3DSURFACE9 surface;		// Con trỏ hướng tới surface

	D3DFORMAT backBufferFormat = D3DFMT_X8R8G8B8;  // format của backBuffer  --> Mặc định
public:
	DeviceManager();
	DeviceManager(DXGraphics*);
	~DeviceManager();

	void ClearScreen();

	void SetDevice(LPDIRECT3DDEVICE9 d3ddv);
	void SetBackBuffer(LPDIRECT3DSURFACE9 backBuffer);
	LPDIRECT3DDEVICE9 GetDevice();
	LPDIRECT3DSURFACE9 GetBackBuffer();

	LPDIRECT3DSURFACE9 GetSurface() { return this->surface; }
};

