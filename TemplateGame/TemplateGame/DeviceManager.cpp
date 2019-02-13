#include "DeviceManager.h"


DeviceManager::DeviceManager()
{
	this->d3d = NULL;
	this->d3ddv = NULL;
	this->backBuffer = NULL;
}

// Khởi tạo thiết bị chạy game
DeviceManager::DeviceManager(DXGraphics* dxGraphics) {
	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = this->backBufferFormat;
	d3dpp.BackBufferWidth = dxGraphics->GetScreenWidth();
	d3dpp.BackBufferHeight = dxGraphics->GetScreenHeight();
	d3dpp.Windowed = TRUE;
	d3dpp.hDeviceWindow = dxGraphics->GetHwnd();
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	const auto rs = this->d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		dxGraphics->GetHwnd(),
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&this->d3ddv);

	if (this->d3ddv == nullptr)
	{
		MessageBox(NULL, L"Error creating Direct3D Device", L"Error", MB_OK);
		trace(L"Error creating Direct3D Device");
	}

	this->d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &this->backBuffer);
}

DeviceManager::~DeviceManager()
{
	if (this->d3ddv != NULL) this->d3ddv->Release();
	if (this->d3d != NULL) this->d3d->Release();
}

// Xóa màn hình hiện hành
void DeviceManager::ClearScreen()
{
	this->d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}

// Get/set methods
void DeviceManager::SetDevice(LPDIRECT3DDEVICE9 d3ddv)
{
	this->d3ddv = d3ddv;
}

void DeviceManager::SetBackBuffer(LPDIRECT3DSURFACE9 backBuffer)
{
	this->backBuffer = backBuffer;
}

LPDIRECT3DDEVICE9 DeviceManager::GetDevice()
{
	return this->d3ddv;
}

LPDIRECT3DSURFACE9 DeviceManager::GetBackBuffer()
{
	return this->backBuffer;
}
