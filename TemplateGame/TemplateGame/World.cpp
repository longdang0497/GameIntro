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
	this->gameCharacter->Update(deltaTime);
}

// Hàm dùng để Render Object lên màn hình
// Lưu ý khi Render là Render cái Map trước (tức là Brick), sau đó là nhân vật chính, tiếp theo là Enemy, cuối cùng là các Item
// Việc này giúp cho việc Render nó trong đẹp hơn
void World::RenderObjects()
{
	this->gameCharacter->Render();
}

vector<D3DXVECTOR2> World::ReadCoord(LPCWSTR filePath, int count)
{
	vector<D3DXVECTOR2> tempVector;
	tempVector.resize(count);

	// Đọc thông tin file
	fstream f;
	try
	{
		f.open(filePath);
	}
	catch (fstream::failure e)
	{
		trace(L"Error when Init Sprite %s", filePath);
	}

	string line;
	int id = 0;
	while (!f.eof() && id < count) {
		getline(f, line);

		string splitString;

		istringstream iss(line);

		vector<int> tempCoord;

		while (getline(iss, splitString, '\t'))
		{
			tempCoord.push_back(stoi(splitString));
		}

		tempVector[id].x = tempCoord[0];
		tempVector[id].y = tempCoord[1];

		//	this->spritePositions->push_back(tempVector);
		id++;
	}

	trace(L"Done Init Sprite %s", filePath);
	f.close();

	return tempVector;
}

//RECT * World::ReadCurrentSpritePosition()
//{
//	RECT * rect = new RECT();
//	vector<int>* tempVector = this->spritePositions->at(this->index);
//
//	// Giá trị đầu tiên là x, giá trị thứ 2 là y
//	rect->left = tempVector->at(0);
//	rect->top = tempVector->at(1);
//	rect->right = rect->left + this->width;
//	rect->bottom = rect->top + this->height;
//
//	return rect;
//}

// Khởi tạo SpriteHandler, Map và Grid
void World::LoadResources(LPDIRECT3DDEVICE9 device)
{
	if (device == NULL) return;

	HRESULT result = D3DXCreateSprite(device, &spriteHandler);

	if (result != D3D_OK)
		trace(L"Lỗi khi tạo Sprite");

	this->grid = new Grid();
	this->gameCharacter = new MainCharacter(spriteHandler);
	this->gameCharacter->SetState(STAND_RIGHT);
	 
	this->InitSprite(device);
	this->InitObjectPosition();
	
}

// Hàm này dùng để khởi tạo Sprite của các Object
void World::InitSprite(LPDIRECT3DDEVICE9 device)
{
	this->texture = new Texture();

	// Start: Insert code here
	LPDIRECT3DTEXTURE9 gameTexture = this->texture->LoadTexture(device, TEXTURE_GAME_CHARACTERS);
	//this->gameCharacter->InitSprites(device, gameTexture);

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	//MAIN_STAND
	spriteCoord = ReadCoord(MAIN_STAND_PATH, MAIN_STAND_COUNT);
	int id = 10001;
	LPANIMATION ani;
	ani = new CAnimation(100);	// stand

	for (int i = 0; i < spriteCoord.size(); i++)
	{
		sprites->Add(id + i, spriteCoord[i], MAIN_STAND_WIDTH, MAIN_STAND_HEIGHT, gameTexture, this->spriteHandler);
		ani->Add(id);
		animations->Add(400, ani, true);

		gameCharacter->AddAnimation(400);		// stand
	}

	spriteCoord.clear();


	// End: Insert Code above

	this->texture = nullptr;
	delete this->texture;
}

// Hàm này dùng để khởi tạo vị trí cho Object và add vào Grid
void World::InitObjectPosition()
{
	this->gameCharacter->InitPostition();
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
