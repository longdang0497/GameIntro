#include "Sprite.h"

Sprite::Sprite(LPD3DXSPRITE spriteHandler, LPDIRECT3DTEXTURE9 texture, LPCWSTR filePath, int count, int width, int height)
{
	
	if (texture == NULL)
		return;
	this->texture = texture;
	this->count = count;
	this->width = width;
	this->height = height;
	this->spriteHandler = spriteHandler;

	// Gan he mau trong suot
	transColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	this->index = 0;

	LPDIRECT3DDEVICE9 d3ddv;
	this->spriteHandler->GetDevice(&d3ddv);	

	this->spritePositions = new vector<vector<int>*>();

	this->SetSpritePositions(filePath);
}

Sprite::Sprite(LPD3DXSPRITE spriteHandler, LPDIRECT3DTEXTURE9 texture, int index, int count, int width, int height)
{
	if (texture == NULL)
		return;
	this->texture = texture;
	this->count = count;
	this->width = width;
	this->height = height;

	this->spriteHandler = spriteHandler;
	// Gan he mau trong suot
	transColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	this->index = 0;

	LPDIRECT3DDEVICE9 d3ddv;
	this->spriteHandler->GetDevice(&d3ddv);

	this->spritePositions = new vector<vector<int>*>();

	vector<int> * positions = new vector<int>();
	positions->push_back((index - 1) * 32);
	positions->push_back(0);
	this->spritePositions->push_back(positions);

}

// Phương thức này dùng để đọc file txt rồi sau đó lưu vào vector (hạn chế việc đọc file)
void Sprite::SetSpritePositions(LPCWSTR filePath)
{

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
	while (!f.eof()) {
		getline(f, line);

		string splitString;

		istringstream iss(line);

		vector<int> * tempVector = new vector<int>();

		while (getline(iss, splitString, '\t'))
		{
			tempVector->push_back(stoi(splitString));
		}

		this->spritePositions->push_back(tempVector);
	}

	trace(L"Done Init Sprite %s", filePath);
	f.close();
}

Sprite::~Sprite() {
	texture->Release();

	for (int i = 0; i < this->spritePositions->size(); i++) {
		delete this->spritePositions->at(i);
	}

	delete this->spritePositions;
}

// Cap nhat vi tri cua sprite tiep theo
void Sprite::UpdateSprite() {
	this->index = (this->index + 1) % count;
}

/*
	x: Toa do vi tri x cua Sprite
	y: Toa do vi tri y cua Sprite
	width: Chieu ngang pixel cua Sprite dang xet
	height: Chieu dai pixel cua Sprite dang xet
	position: Vi tri xua hien tren man hinh theo 3 truc (x, y, z)
*/

//draw 1 sprite
void Sprite::DrawSprite(int x, int y, D3DXVECTOR3 position) {
	if (this->spriteHandler == NULL || this->texture == NULL)
		return;

	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + this->width;
	rect.bottom = y + this->height;

	//using this line for camera only
	this->spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	D3DXMATRIX mat;

	D3DXMatrixTransformation(&mat, NULL, NULL, NULL, NULL, NULL, &position);

	this->spriteHandler->SetTransform(&mat);

	this->spriteHandler->Draw(this->texture, &rect, NULL, NULL, this->transColor);
	this->spriteHandler->End();
}

// draw multi sprites
// flagRight dùng để xác định được là sprite đang quay qua trái hay phải, điều này giúp cho tiết kiệm việc khởi tạo Sprite ban đầu
void Sprite::DrawSprite(D3DXVECTOR3 position, bool flagRight) {
	if (this->spriteHandler == NULL || this->texture == NULL)
		return;

	RECT* rect = ReadCurrentSpritePosition();	//đọc tọa độ của sprite trong file txt

	//this->spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	this->spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	// Texture being used is width by height:
	D3DXVECTOR3 spriteCentre = D3DXVECTOR3((float)width, (float)height, 0);

	// Build our matrix to rotate, scale and position our sprite
	D3DXMATRIX mat;

	// Biến này làm cho object quay theo trục X (trục dọc)
	float tempTurnRight = 1.0f;

	if (!flagRight) {
		tempTurnRight = -1.0f;
	}

	D3DXVECTOR3 scaling(tempTurnRight, 1.0f, 1.0f);

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation(&mat, &D3DXVECTOR3(width / 2, height / 2, 0), NULL, &scaling, &spriteCentre, NULL, &position);

	this->spriteHandler->SetTransform(&mat);

	this->spriteHandler->Draw(this->texture, rect, NULL, NULL, this->transColor);
	this->spriteHandler->End();
	delete rect;
}

void Sprite::Reset()
{
	index = 0;
}

RECT* Sprite::ReadCurrentSpritePosition()
{

	RECT * rect = new RECT();
	vector<int>* tempVector = this->spritePositions->at(this->index);
	
	// Giá trị đầu tiên là x, giá trị thứ 2 là y
	rect->left = tempVector->at(0);
	rect->top = tempVector->at(1);
	rect->right = rect->left + this->width;
	rect->bottom = rect->top + this->height;

	return rect;
}

void Sprite::SetWidth(int value)
{
	this->width = value;
}

int Sprite::GetWidth()
{
	return this->width;
}

void Sprite::SetHeight(int value)
{
	this->height = value;
}

int Sprite::GetHeight()
{
	return this->height;
}

int Sprite::GetIndex()
{
	return this->index;
}

int Sprite::GetCount()
{
	return this->count;
}