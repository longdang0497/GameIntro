#include "Sprite.h"
#include <vector>

Sprite::Sprite(LPD3DXSPRITE spriteHandler, LPDIRECT3DTEXTURE9 texture, LPWSTR coord, int count, int width, int height)
{
	this->count = count;
	this->width = width;
	this->height = height;
	this->spriteHandler = spriteHandler;
	this->coord = coord;
	this->texture = texture;
	if (this->texture == NULL)
		return;

	// Gan he mau trong suot
	transColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	this->index = 0;

	LPDIRECT3DDEVICE9 d3ddv;
	this->spriteHandler->GetDevice(&d3ddv);	
}

Sprite::~Sprite() {
	texture->Release();
	delete(coord);
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

//draw multi sprites
void Sprite::DrawSprite(D3DXVECTOR3 position) {
	if (this->spriteHandler == NULL || this->texture == NULL)
		return;
	RECT rect = ReadCoord();

	D3DXVECTOR3 pos(0, 0, 0);

	this->spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	// Texture being used is width by height:
	D3DXVECTOR3 spriteCentre = D3DXVECTOR3((float)width, (float)height, 0);

	// Build our matrix to rotate, scale and position our sprite
	D3DXMATRIX mat;

	D3DXVECTOR3 scaling(1.0f, 1.0f, 1.0f);

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation(&mat, &D3DXVECTOR3(width / 2, height / 2, 0), NULL, &scaling, &spriteCentre, NULL, &position);

	this->spriteHandler->SetTransform(&mat);
	this->spriteHandler->Draw(this->texture, &rect, NULL, NULL, this->transColor);

	this->spriteHandler->End();
}

void Sprite::Reset()
{
	index = 0;
}

RECT Sprite::ReadCoord()
{
	//init array Sprite's position
	vector<vector<int>> arrCoord;
	arrCoord.resize(this->count);

	//Read file info of file
	fstream f;
	try
	{
		f.open(this->coord);
	}
	catch (fstream::failure e)
	{
		MessageBox(NULL, L"[Sprite class]--Read sprite info from file failed", L"Error", NULL);
	}
	string line;
	int id = 0;
	while (!f.eof() && id < this->count)
	{
		vector<string> pos;
		string split;
		getline(f, line);
		istringstream iss(line);

		while (getline(iss, split, '\t'))
		{
			pos.push_back(split);
		}

		for (int i = 0; i < arrCoord.size(); i++)
			arrCoord[i].resize(2);

		//lưu hoành độ x
		arrCoord[id][0] = stoi(pos[0]);
		srect.left = arrCoord[id][0];

		//lưu tung độ y
		arrCoord[id][1] = stoi(pos[1]);
		srect.top = arrCoord[id][1];

		srect.right = srect.left + width;
		srect.bottom = srect.top + height + 1;

		if (id == index)
		{
			break;
		}
		id++;
	}
	f.close();
	return srect;
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