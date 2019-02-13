#include "GameManager.h"

void GameManager::InitBackground()
{
}

void GameManager::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	//world->InitSprites(d3ddv);
}

void GameManager::InitPositions()
{
}

GameManager::GameManager(HINSTANCE hInstance, LPWSTR name, int mode, int isFullScreen, int frameRate)
	:MetroidGame(hInstance, name, mode, isFullScreen, frameRate)
{
	tickPerFrame = 1000 / this->dxGraphics->GetFrameRate();

	//sound = new GameSound();
}

GameManager::~GameManager()
{
	/*delete(this->world);
	delete(this->intro);
	delete(this->appear);
	delete(this->sound);
	delete(this->grid);*/
}

/*
	Khoi tao Spritehandler va Texture cho game
*/
void GameManager::LoadResources(LPDIRECT3DDEVICE9 d3ddev)
{
	//---------Khởi tạo spriteHandler---------------
	if (d3ddev == NULL) return;

	HRESULT result = D3DXCreateSprite(d3ddev, &this->spriteHandler);
	if (result != D3D_OK)
		trace(L"Unable to create SpriteHandler");

	//texture = texture.loadTexture(d3ddev, BRICK_TEXTURE);
	//if (texture == NULL)
		//trace(L"Unable to load BrickTexture");

	srand((unsigned)time(NULL));
	this->InitSprites(d3ddev);
	this->InitPositions();
}

void GameManager::Update(float Delta)
{
	//world->Update(Delta);
}

void GameManager::Render(LPDIRECT3DDEVICE9 d3ddv)
{
	//world->Render();
	//map->drawMap();
}

void GameManager::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta)
{
}

void GameManager::OnKeyDown(int KeyCode)
{
}

void GameManager::OnKeyUp(int KeyCode)
{
}

DWORD GameManager::GetTickPerFrame()
{
	return this->tickPerFrame;
}

LPD3DXSPRITE GameManager::GetSpriteHandler()
{
	return this->spriteHandler;
}
