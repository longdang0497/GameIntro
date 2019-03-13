#include "Brick.h"



Brick::Brick()
{
	this->isActive = true;
}

// x là column, y là row
Brick::Brick(LPD3DXSPRITE spriteHandler, int index, int x, int y)
{
	this->isActive = true;
	this->spriteHandler = spriteHandler;
	this->index = index;
	this->objectType = BRICK;

	this->objectWidth = BRICK_SIZE;
	this->objectHeight = BRICK_SIZE;

	this->SetPosition(x*32.0f, y*32.0f);
	this->SetVeclocity(0, 0);
}

void Brick::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	this->sprite = new Sprite(this->spriteHandler, texture, this->index, 1, BRICK_SIZE, BRICK_SIZE);
}

void Brick::InitPostition()
{

}

void Brick::Reset(float x, float y)
{
}

void Brick::Update(float t, vector<Object*>* object)
{
}

void Brick::Render()
{
	if (!this->isActive)
		return;
	else {
		D3DXVECTOR3 position;
		position.x = this->curPos->GetPosX();
		position.y = this->curPos->GetPosY();
		position.z = 0;

		this->sprite->DrawSprite(position, true);
	}
}

void Brick::Destroy()
{
}


bool Brick::handleCollision(Object * otherObject)
{
	return false;
}

Brick::~Brick()
{
	delete this->sprite;
}
