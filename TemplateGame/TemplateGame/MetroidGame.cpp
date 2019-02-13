#include "MetroidGame.h"

MetroidGame::MetroidGame()
{
}

// Khởi tạo game
MetroidGame::MetroidGame(HINSTANCE hInstance, LPCWSTR nameOfGame, int mode, bool isFullScreen, int frameRate)
{
	this->dxGraphics = new DXGraphics(hInstance, nameOfGame, mode, frameRate, isFullScreen);
	this->input = new Input(hInstance, this->dxGraphics->getHwnd());
	this->deviceManager = new DeviceManager(this->dxGraphics);
}


MetroidGame::~MetroidGame()
{
	delete(this->deviceManager);
	delete(this->input);
	delete(this->dxGraphics);
}

// Chạy Game
void MetroidGame::GameRun()
{
	MSG msg;
	int done = 0;
	DWORD frameStartTime = GetTickCount();

	DWORD tickPerFrame = 100 / this->dxGraphics->getFrameRate();

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;
			else if (msg.message == WM_ACTIVATE) {
				if (this->input->getKeyboard() != NULL && this->input->getKeyboard()->Poll() != DI_OK) {
					this->input->getKeyboard()->Acquire();
				}
				msg.message = 0;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


		DWORD now = GetTickCount();
		this->deltaTime = now - frameStartTime;
		if (this->deltaTime >= tickPerFrame)
		{
			frameStartTime = now;
			Update(this->deltaTime / 1000.0f);
			this->RenderFrame();

		}
		else {
			Sleep(tickPerFrame);
		}

		this->input->ProcessEscKeyCode();
		this->checkKey();

		ProcessInput(this->deviceManager->GetDevice(), this->deltaTime);

	}
}

// Mặc định
void MetroidGame::checkKey()
{
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = this->input->getKeyboard()->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), this->input->getKeyEvents(), &dwElements, 0);

	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = this->input->getKeyEvents()[i].dwOfs;
		int KeyState = this->input->getKeyEvents()[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}

// Dùng để render 1 frame lên màn ảnh
void MetroidGame::RenderFrame()
{
	auto result = this->deviceManager->GetDevice()->BeginScene();

	if (result == D3D_OK)
	{
		// Clear back buffer with BLACK
		this->deviceManager->ClearScreen();

		//if (camera)
		//{
		//	camera->SetTransform(_device);
		//}

		Render(this->deviceManager->GetDevice());
		this->deviceManager->GetDevice()->EndScene();
	}

	this->deviceManager->GetDevice()->Present(NULL, NULL, NULL, NULL);
}

void MetroidGame::Update(float deltaTime)
{
}

void MetroidGame::Render(LPDIRECT3DDEVICE9)
{
}

void MetroidGame::LoadResources(LPDIRECT3DDEVICE9)
{
}

void MetroidGame::ProcessInput(LPDIRECT3DDEVICE9, float)
{
}

// Xử lý khi nhấn phím
void MetroidGame::OnKeyDown(int keyCode)
{
}

// Xử lý khi thả phím ra
void MetroidGame::OnKeyUp(int keyCode)
{
}


