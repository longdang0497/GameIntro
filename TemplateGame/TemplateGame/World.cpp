#include "World.h"
#include "World.h"
#include "World.h"
#include "World.h"
#include "World.h"
#include "World.h"
#include "World.h"
#include "World.h"
#include "World.h"


World::World()
{
	
}

// Hàm này dùng để khởi tạo các Object ban đầu (chỉ khởi tạo chứu không xét vị trí gì hết)
World::World(LPDIRECT3DDEVICE9 device)
{
	this->LoadResources(device);
}

World::~World()
{
}

// Hàm dùng để cập nhật lại vị trí của các Object
void World::UpdateObjects(float deltaTime)
{
}

// Hàm dùng để Render Object lên màn hình
// Lưu ý khi Render là Render cái Map trước (tức là Brick), sau đó là nhân vật chính, tiếp theo là Enemy, cuối cùng là các Item
// Việc này giúp cho việc Render nó trong đẹp hơn
void World::RenderObjects()
{
}

// Khởi tạo SpriteHandler, Map và Grid
void World::LoadResources(LPDIRECT3DDEVICE9 device)
{
	if (device == NULL) return;

	HRESULT result = D3DXCreateSprite(device, &spriteHandler);

	if (result != D3D_OK)
		trace(L"Lỗi khi tạo Sprite");

	this->grid = new Grid();

	this->InitSprite(device);
	this->InitObjectPosition();
	
}

// Hàm này dùng để khởi tạo Sprite của các Object
void World::InitSprite(LPDIRECT3DDEVICE9 device)
{
	this->texture = new Texture();

	// Start: Insert code here

	// End: Insert Code above

	this->texture = nullptr;
	delete this->texture;
}

// Hàm này dùng để khởi tạo vị trí cho Object và add vào Grid
void World::InitObjectPosition()
{
}

void World::SetGrid(Grid * grid)
{
	this->grid = grid;
}

Grid * World::GetGrid()
{
	return this->grid;
}

void World::SetTexture(Texture * texture)
{
	this->texture = texture;
}

Texture * World::GetTexture()
{
	return this->texture;
}
