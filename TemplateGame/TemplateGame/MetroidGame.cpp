#include "MetroidGame.h"

MetroidGame::MetroidGame()
{
}

// Khởi tạo game
MetroidGame::MetroidGame(HINSTANCE hInstance, LPCWSTR nameOfGame, int mode, bool isFullScreen, int frameRate)
{
	this->dxGraphics = new DXGraphics(hInstance, nameOfGame, mode, frameRate, isFullScreen);
	this->input = new Input(hInstance, this->dxGraphics->GetHwnd());
	this->deviceManager = new DeviceManager(this->dxGraphics);

	this->gameMode = GAME_MODE_RUN;

	this->world = new World(this->deviceManager->GetDevice());
}

MetroidGame::~MetroidGame()
{
	this->world = nullptr;
	delete this->world;

	this->deviceManager = nullptr;
	delete(this->deviceManager);

	this->input = nullptr;
	delete(this->input);

	this->dxGraphics = nullptr;
	delete(this->dxGraphics);
}

// Chạy Game
void MetroidGame::GameRun()
{
	MSG msg;
	int done = 0;
	DWORD frameStartTime = GetTickCount();

	DWORD tickPerFrame = 100 / this->dxGraphics->GetFrameRate();

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;
			else if (msg.message == WM_ACTIVATE) {
				if (this->input->GetKeyboard() != NULL && this->input->GetKeyboard()->Poll() != DI_OK) {
					this->input->GetKeyboard()->Acquire();
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
			this->UpdateBelongToGameMode(this->deltaTime / 1000.0f);
			this->RenderFrame();

		}
		else {
			Sleep(tickPerFrame);
		}

		this->input->ProcessEscKeyCode();
		this->CheckKey();

		ProcessInput(this->deviceManager->GetDevice(), this->deltaTime);

	}
}

// Mặc định
void MetroidGame::CheckKey()
{
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = this->input->GetKeyboard()->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), this->input->GetKeyEvents(), &dwElements, 0);

	for (DWORD i = 0; i < dwElements; i++)
	{
		int keyCode = this->input->GetKeyEvents()[i].dwOfs;
		int keyState = this->input->GetKeyEvents()[i].dwData;
		if ((keyState & 0x80) > 0)
			OnKeyDown(keyCode);
		else
			OnKeyUp(keyCode);
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

		this->RenderBelongToGameMode();
		this->deviceManager->GetDevice()->EndScene();
	}

	this->deviceManager->GetDevice()->Present(NULL, NULL, NULL, NULL);
}

void MetroidGame::UpdateBelongToGameMode(float deltaTime)
{
	switch (this->gameMode)
	{
	case GAME_MODE_INTRO:
		break;
	case GAME_MODE_START:
		break;
	case GAME_MODE_RUN:
		// this->camera->Update();
		// this->world->GetGrid()->SetDeltaTime(deltaTime);
		// this->world->GetMap()->UpdateMap();
		this->UpdateObjects(deltaTime);
		break;
	case GAME_MODE_END:
		break;
	default:
		break;
	}
}

void MetroidGame::UpdateObjects(float deltaTime)
{
	this->world->UpdateObjects(deltaTime);

	//if (world->samus->isSamusDeath() == true)
	//{
	//	screenMode = GAMEMODE_GAMEOVER;
	//	return;
	//}
}

void MetroidGame::RenderBelongToGameMode()
{
	switch (this->gameMode)
	{
	case GAME_MODE_INTRO:
		break;
	case GAME_MODE_START:
		break;
	case GAME_MODE_RUN:
		this->RenderObjects();
		break;
	case GAME_MODE_END:
		break;
	default:
		break;
	}
}

void MetroidGame::RenderObjects()
{
	this->world->RenderObjects();
}

void MetroidGame::ProcessInput(LPDIRECT3DDEVICE9, float)
{
	ObjectVelocity * temp = new ObjectVelocity();
	
	if (input->IsKeyDown(DIK_RIGHT))
	{
		temp->SetVx(world->GetMainCharacter()->GetCurVec()->GetVx() + CHARACTER_SPEED);
		temp->SetVy(0);
		world->GetMainCharacter()->SetCurVec(temp);
		world->GetMainCharacter()->SetState(RUN_RIGHT);
	}
	if (input->IsKeyDown(DIK_LEFT))
	{
		temp->SetVx(world->GetMainCharacter()->GetCurVec()->GetVx() - CHARACTER_SPEED);
		temp->SetVy(0);
		world->GetMainCharacter()->SetCurVec(temp);
		world->GetMainCharacter()->SetState(RUN_LEFT);
	}
	else
	{
		temp->SetVx(0);
		temp->SetVy(0);
		world->GetMainCharacter()->SetCurVec(temp);
		if (world->GetMainCharacter()->GetLastVec() > 0)
		{
			if (world->GetMainCharacter()->GetState() == RUN_RIGHT)
			{
				world->GetMainCharacter()->ResetAllSprites();
				world->GetMainCharacter()->SetState(STAND_RIGHT);				
			}
		}
		else if (world->GetMainCharacter()->GetLastVec() < 0)
		{
			world->GetMainCharacter()->ResetAllSprites();
			world->GetMainCharacter()->SetState(STAND_LEFT);
		}
	}
}

// Xử lý khi nhấn phím
void MetroidGame::OnKeyDown(int keyCode)
{
}

// Xử lý khi thả phím ra
void MetroidGame::OnKeyUp(int keyCode)
{
}


