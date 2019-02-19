#include "Sprite.h"
#include <vector>

Sprite::Sprite(LPD3DXSPRITE SpriteHandler, LPDIRECT3DTEXTURE9 texture, LPWSTR _coord, int count)
{
	this->count = count;
	spriteHandler = SpriteHandler;
	this->_Coord = _coord;

	// Gan he mau trong suot
	transColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	this->_Index = 0;

	this->width = width;
	this->height = height;

	LPDIRECT3DDEVICE9 d3ddv;
	SpriteHandler->GetDevice(&d3ddv);

	this->texture = texture;
	if (this->texture == NULL)
		return;
}

Sprite::~Sprite() {
	texture->Release();
	delete(_Coord);
}

// Cap nhat vi tri cua sprite tiep theo
void Sprite::updateSprite() {
	this->_Index = (this->_Index + 1) % count;
}

/*
	x: Toa do vi tri x cua Sprite
	y: Toa do vi tri y cua Sprite
	width: Chieu ngang pixel cua Sprite dang xet
	height: Chieu dai pixel cua Sprite dang xet
	position: Vi tri xua hien tren man hinh theo 3 truc (x, y, z)
*/

//draw 1 sprite
void Sprite::drawSprite(int x, int y, int width, int height, D3DXVECTOR3 position) {
	if (this->spriteHandler == NULL || this->texture == NULL)
		return;

	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + width;
	rect.bottom = y + height;

	//using this line for camera only
	this->spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	D3DXMATRIX mat;

	D3DXMatrixTransformation(&mat, NULL, NULL, NULL, NULL, NULL, &position);

	this->spriteHandler->SetTransform(&mat);

	this->spriteHandler->Draw(this->texture, &rect, NULL, NULL, this->transColor);
	this->spriteHandler->End();
}

//draw multi sprites
void Sprite::drawSprite(int width, int height, D3DXVECTOR3 position) {
	if (this->spriteHandler == NULL || this->texture == NULL)
		return;
	RECT rect;
	rect = ReadCoord();

	D3DXVECTOR3 pos(0, 0, 0);
	//pos.x = position.x;
	//pos.y = position.y;

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

void Sprite::ReSet()
{
	_Index = 0;
}

RECT Sprite::ReadCoord()
{
	//init array Sprite's position
	vector<vector<int>> coord;
	coord.resize(count);

	//Read file info of file
	fstream f;
	try
	{
		f.open(_Coord);
	}
	catch (std::fstream::failure e)
	{
		MessageBox(NULL, L"[Sprite class]--Read sprite info from file failed", L"Error", NULL);
	}
	string line;
	int id = 0;
	while (!f.eof() && id < count)
	{
		vector<string> pos;
		string split;
		Getline(f, line);
		istringstream iss(line);

		while (Getline(iss, split, '\t'))
		{
			pos.push_back(split);
		}

		for (int i = 0; i < coord.size(); i++)
			coord[i].resize(2);

		coord[id][0] = stoi(pos[0]);
		srect.left = coord[id][0];

		coord[id][1] = stoi(pos[1]);
		srect.top = coord[id][1];

		srect.right = srect.left + width;
		srect.bottom = srect.top + height + 1;

		if (id == _Index)
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
	width = value;
}

int Sprite::GetWidth()
{
	return width;
}

void Sprite::SetHeight(int value)
{
	height = value;
}

int Sprite::GetHeight()
{
	return height;
}

int Sprite::GetIndex()
{
	return this->_Index;
}

int Sprite::GetCount()
{
	return count;
}