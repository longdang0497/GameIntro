#include "GameManager.h"

void GameManager::_InitBackground()
{
}

void GameManager::_InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	//world->InitSprites(d3ddv);
}

void GameManager::_InitPositions()
{
}

GameManager::GameManager(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate)
	:MetroidGame(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	tick_per_frame = 1000 / this->dxGraphics->getFrameRate();

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

	HRESULT result = D3DXCreateSprite(d3ddev, &spriteHandler);
	if (result != D3D_OK)
		trace(L"Unable to create SpriteHandler");

	//_texture = texture.loadTexture(d3ddev, BRICK_TEXTURE);
	//if (_texture == NULL)
		//trace(L"Unable to load BrickTexture");

	srand((unsigned)time(NULL));
	this->_InitSprites(d3ddev);
	this->_InitPositions();
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
	return this->tick_per_frame;
}

LPD3DXSPRITE GameManager::getSpriteHandler()
{
	return this->spriteHandler;
}
