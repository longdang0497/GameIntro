﻿#include "ProcessGame.h"

ProcessGame *ProcessGame::_instance = NULL;

ProcessGame::ProcessGame(HINSTANCE hInstance, int nShowCmd)
{
	Graphic *graphic = Graphic::GetInstance(hInstance, nShowCmd, GAME_TITLE, GAME_MODE_640_480);
	/*SetWindowPos(graphic->GetHWnd(), 0, 0, 0, graphic->GetWidth(), graphic->GetHeight(), SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);*/

	Game *game = Game::GetInstance();
	game->Init(graphic->GetHWnd());
	
	this->keyHandler = new KeyEventHandler();
	game->InitKeyboard(this->keyHandler);


	World *world = World::GetInstance();
	world->LoadResource();
}

// Các xử lý update và hiển thị nhân vật
int ProcessGame::GameRun()
{
	MSG msg;
	int done = 0;

	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		DWORD deltaTime = now - frameStart;

		if (deltaTime >= tickPerFrame)
		{
			frameStart = now;

			Game::GetInstance()->ProcessKeyboard();

			this->Update(deltaTime);
			this->Render();
		}
		else
			Sleep(tickPerFrame - deltaTime);
	}

	return 1;
}

void ProcessGame::Update(DWORD dt)
{

}

void ProcessGame::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();

	if (d3ddv->BeginScene()) {
		d3ddv->ColorFill(Game::GetInstance()->GetBackBuffer(), NULL, D3DCOLOR_XRGB(0, 0, 0));
		Game::GetInstance()->GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);
		
		World::GetInstance()->Render();

		//RECT rect;
		//rect.top = 0;
		//rect.left = 0;
		//rect.right = 600;
		//rect.bottom = 300;

		//LPDIRECT3DSURFACE9 surface;
		//LPDIRECT3DSURFACE9 backbuffer = Game::GetInstance()->GetBackBuffer();
		//// create surface
		//Game::GetInstance()->GetDirect3DDevice()->CreateOffscreenPlainSurface(
		//	640, // width
		//	480, // height
		//	D3DFMT_X8R8G8B8,
		//	D3DPOOL_DEFAULT,
		//	&surface,
		//	NULL
		//);

		//D3DXLoadSurfaceFromFile(
		//	surface,
		//	NULL,
		//	NULL,
		//	L"sprite\\background.png",
		//	NULL,
		//	D3DX_DEFAULT,
		//	0,
		//	NULL
		//);

		//Game::GetInstance()->GetDirect3DDevice()->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

		//Game::GetInstance()->GetDirect3DDevice()->StretchRect(surface, NULL, backbuffer, NULL, D3DTEXF_NONE);


		Game::GetInstance()->GetSpriteHandler()->End();
		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}


// Xử lý sự kiện input
void KeyEventHandler::KeyState(BYTE * states)
{

}

void KeyEventHandler::OnKeyDown(int KeyCode)
{
	OutputDebugString(L"Nhấn phím");
}

void KeyEventHandler::OnKeyUp(int KeyCode)
{
}