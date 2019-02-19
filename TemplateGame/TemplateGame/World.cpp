#include "World.h"


World::World()
{
	
}

World::World(LPDIRECT3DDEVICE9 device)
{
	this->LoadResources(device);
}

World::~World()
{
}

// Khởi tạo SpriteHandler và Texture cho game
void World::LoadResources(LPDIRECT3DDEVICE9 device)
{
	if (device == NULL) return;

	HRESULT result = D3DXCreateSprite(device, &spriteHandler);

	if (result != D3D_OK)
		trace(L"Lỗi khi tạo Sprite");

	
}

void World::SetGrid(Grid * grid)
{
	this->grid = grid;
}

Grid * World::GetGrid()
{
	return this->grid;
}
