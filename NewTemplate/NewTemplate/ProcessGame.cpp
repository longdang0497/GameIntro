#include "ProcessGame.h"

ProcessGame *ProcessGame::_instance = NULL;

ProcessGame::ProcessGame(HINSTANCE hInstance, int nShowCmd)
{
	Graphic *graphic = Graphic::GetInstance(hInstance, nShowCmd, GAME_TITLE, GAME_MODE_256_256);

	Game *game = Game::GetInstance();

	game->Init(graphic->GetHWnd());

	CKeyBoard::Create(hInstance, graphic->GetHWnd());
	
	
	/*this->keyHandler = new KeyEventHandler();
	game->InitKeyboard(this->keyHandler);*/

	Texture *texture = Texture::GetInstance();
	texture->Add(ID_TEXTURE_MAIN, PATH_TEXTURE_MAIN);
	texture->Add(ID_TEXTURE_MAP_1, PATH_TEXTURE_MAP_1);
	texture->Add(ID_TEXTURE_MAP_2, PATH_TEXTURE_MAP_2);
	texture->Add(ID_TEXTURE_MAP_3, PATH_TEXTURE_MAP_3);
	texture->Add(ID_TEX_FONT, PATH_TEX_FONT);
	texture->Add(ID_TEX_HUD_BG, PATH_TEX_HUD_BG);
	texture->Add(ID_TEX_HEALTH, PATH_TEX_HEALTH);
	texture->Add(ID_BB, PATH_BB);
	texture->Add(ID_TEXTURE_BLACK, PATH_TEXTURE_BLACK);

	texture->Add(ID_TEXTURE_ENEMIES, PATH_TEXTURE_ENEMIES);
	


	Grid* grid = Grid::GetInstance(1, 1, true);

	Time = GetTickCount();
	alpha = 255;

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
		CKeyBoard::getInstance()->PollKeyboard();
		CKeyBoard::getInstance()->UpdateKeyboard();
		CKeyGame::getInstance()->update();

		// dt: the time between (beginning of last frame) and now
		DWORD deltaTime = now - frameStart;

		if (deltaTime >= tickPerFrame)
		{
			frameStart = now;

			//Game::GetInstance()->ProcessKeyboard();

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
	switch (Game::GetInstance()->GetGameStage())
	{
	case STAGE1:
		Stage1::GetInstance()->Update(dt);
		break;
	case STAGE2:
		Stage2::GetInstance()->Update(dt);
		break;
	case STAGE3:
		Stage3::GetInstance()->Update(dt);
		break;
	default:
		break;
	}
}

void ProcessGame::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();

	if (d3ddv->BeginScene()) {
		d3ddv->ColorFill(Game::GetInstance()->GetBackBuffer(), NULL, D3DCOLOR_XRGB(0, 0, 0));
		Game::GetInstance()->GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);
		
		switch (Game::GetInstance()->GetGameStage())
		{
		case STAGE1:
			Stage1::GetInstance()->Render();
			break;
		case STAGE2:
			Stage2::GetInstance()->Render();
			break;
		case STAGE3:
			Stage3::GetInstance()->Render();
			break;
		default:
			break;
		}

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


}

void KeyEventHandler::OnKeyUp(int KeyCode)
{

}