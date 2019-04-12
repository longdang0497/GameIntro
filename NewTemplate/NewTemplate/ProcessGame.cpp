#include "ProcessGame.h"

ProcessGame *ProcessGame::_instance = NULL;

ProcessGame::ProcessGame(HINSTANCE hInstance, int nShowCmd)
{
	Graphic *graphic = Graphic::GetInstance(hInstance, nShowCmd, GAME_TITLE, GAME_MODE_640_480);

	Game *game = Game::GetInstance();

	game->Init(graphic->GetHWnd());

	CKeyBoard::Create(hInstance, graphic->GetHWnd());
	
	
	/*this->keyHandler = new KeyEventHandler();
	game->InitKeyboard(this->keyHandler);*/

	Texture *texture = Texture::GetInstance();
	texture->Add(ID_TEXTURE_MAIN, PATH_TEXTURE_MAIN);
	texture->Add(ID_TEXTURE_MAP_1, PATH_TEXTURE_MAP_1);
	texture->Add(ID_TEXTURE_MAP_2, PATH_TEXTURE_MAP_2);
	texture->Add(ID_BB, PATH_BB);


	Grid* grid = Grid::GetInstance(1, 1, true);
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
//	MainCharacter* mainCharacter = MainCharacter::GetInstance();
//	MAIN_CHARACTER_STATE mainState = mainCharacter->GetState();
//
//	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT)) {
//		MainCharacter::GetInstance()->SetVeclocity(0.2f, 0);
//		MainCharacter::GetInstance()->SetState(RUN_RIGHT);
//	}
//
//	if (Game::GetInstance()->IsKeyDown(DIK_LEFT)) {
//		MainCharacter::GetInstance()->SetVeclocity(-0.2f, 0);
//		MainCharacter::GetInstance()->SetState(RUN_LEFT);
//	}
//
//	if (Game::GetInstance()->IsKeyDown(DIK_DOWN)) {
//		if (mainCharacter->GetState() == RUN_RIGHT || mainCharacter->GetState() == STAND_RIGHT) {
//			mainCharacter->SetVeclocity(0, 0);
//			mainCharacter->SetPosition(mainCharacter->GetPosition().x, mainCharacter->GetPosition().y + 10);
//			mainCharacter->SetState(SIT_RIGHT);
//		}
//		else if (mainState == RUN_LEFT || mainState == STAND_LEFT) {
//			mainCharacter->SetVeclocity(0, 0);
//			mainCharacter->SetState(SIT_LEFT);
//		}
//	}
}

void KeyEventHandler::OnKeyUp(int KeyCode)
{
	/*if (KeyCode == DIK_RIGHT) {
		MainCharacter::GetInstance()->SetVeclocity(0, 0);
		MainCharacter::GetInstance()->SetState(STAND_RIGHT);
	}

	if (KeyCode == DIK_LEFT) {
		MainCharacter::GetInstance()->SetVeclocity(0, 0);
		MainCharacter::GetInstance()->SetState(STAND_LEFT);
	}*/
}