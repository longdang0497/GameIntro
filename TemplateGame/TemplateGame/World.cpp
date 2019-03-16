#include "World.h"


World::World()
{
	
}

// Hàm này dùng để khởi tạo các Object ban đầu (chỉ khởi tạo chứu không xét vị trí gì hết)
World::World(LPDIRECT3DDEVICE9 device)
{
	this->objects = new vector<Object*>();
	this->LoadResources(device);
}

World::~World()
{
	for (UINT i = 0; i < this->objects->size(); i++) {
		delete this->objects->at(i);
	}
	delete this->objects;
}

// Hàm dùng để cập nhật lại vị trí của các Object
void World::UpdateObjects(float deltaTime)
{
	for (UINT i = 0; i < this->objects->size(); i++) {
		if (this->objects->at(i)->GetObjectType() != BRICK) {
			vector<Object*> *collisionObjects = this->grid->GetCollisionObjects(this->objects->at(i));
			this->objects->at(i)->Update(deltaTime, collisionObjects);

			for (UINT j = 0; j < collisionObjects->size(); j++) {
				this->grid->UpdateGrid(collisionObjects->at(j));
			}

			delete collisionObjects;
		}

	}
}

// Hàm dùng để Render Object lên màn hình
// Lưu ý khi Render là Render cái Map trước (tức là Brick), sau đó là nhân vật chính, tiếp theo là Enemy, cuối cùng là các Item
// Việc này giúp cho việc Render nó trong đẹp hơn
void World::RenderObjects()
{
	for (UINT i = 0; i < this->objects->size(); i++) {
		this->objects->at(i)->Render();
	}
}

// Khởi tạo SpriteHandler, Map và Grid
void World::LoadResources(LPDIRECT3DDEVICE9 device)
{
	if (device == NULL) return;

	HRESULT result = D3DXCreateSprite(device, &spriteHandler);

	if (result != D3D_OK)
		trace(L"Lỗi khi tạo Sprite");

	this->grid = new Grid(500,600);

	this->gameCharacter = new MainCharacter(spriteHandler);
	this->objects->push_back(this->gameCharacter);
	this->InitMap(TEST_MAP_PATH, spriteHandler);

	this->InitSprite(device);
	this->InitObjectPosition();
	
}

// Hàm này dùng để khởi tạo Sprite của các Object
void World::InitSprite(LPDIRECT3DDEVICE9 device)
{
	this->texture = new Texture();

	// Start: Insert code here
	LPDIRECT3DTEXTURE9 gameTexture = this->texture->LoadTexture(device, TEXTURE_GAME_CHARACTERS);
	this->gameCharacter->InitSprites(device, gameTexture);

	LPDIRECT3DTEXTURE9 brickTexture = this->texture->LoadTexture(device, BRICK_TEXTURE);
	for (UINT i = 0; i < this->objects->size(); i++) {
		if (this->objects->at(i)->GetObjectType() == BRICK) {
			this->objects->at(i)->InitSprites(device, brickTexture);
		}
	}

	// End: Insert Code above

	delete this->texture;
}

// Hàm này dùng để khởi tạo vị trí cho Object và add vào Grid
void World::InitObjectPosition()
{
	this->gameCharacter->InitPostition();
	for (UINT i = 0; i < this->objects->size(); i++) {
		this->grid->Add(this->objects->at(i));
	}
}

void World::InitMap(LPCWSTR path, LPD3DXSPRITE spriteHandler)
{
	fstream f;
	try {
		f.open(path);
	}
	catch (fstream::failure e) {
		trace(L"Error when Init map %s", path);
	}

	string line;
	vector<vector<int> *> * bricks = new vector<vector<int>*>();

	while (!f.eof()) {
		getline(f, line);

		string splitString;

		istringstream iss(line);

		vector<int> * tempVector = new vector<int>();

		while (getline(iss, splitString, ',')) {
			tempVector->push_back(stoi(splitString));
		}

		bricks->push_back(tempVector);
	}

	for (UINT row = 0; row < bricks->size(); row++) {
		for (UINT column = 0; column < bricks->at(row)->size(); column++) {
			int index = bricks->at(row)->at(column);

			if (index != 0) {
				Brick * b = new Brick(spriteHandler, index, column, row);
				this->objects->push_back(b);
			}
		}
	}
	f.close();
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

MainCharacter * World::GetMainCharacter()
{
	return this->gameCharacter;
}
