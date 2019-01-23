#pragma once
#include "DXGraphics.h"

class DeviceManager
{
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddv;		// Dùng để render
	LPDIRECT3DSURFACE9 backBuffer;	// con trỏ hướng tới backbuffer

	D3DFORMAT backBufferFormat = D3DFMT_X8R8G8B8;  // format của backBuffer  --> Mặc định
public:
	DeviceManager();
	DeviceManager(DXGraphics*);
	~DeviceManager();

	void clearScreen();

	void setDevice(LPDIRECT3DDEVICE9 d3ddv);
	void setBackBuffer(LPDIRECT3DSURFACE9 backBuffer);
	LPDIRECT3DDEVICE9 getDevice();
	LPDIRECT3DSURFACE9 getBackBuffer();
};

