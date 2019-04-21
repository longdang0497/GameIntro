#include "Butterfly.h"

Butterfly::Butterfly(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->fly = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_BUTTERFLY);
	this->SetObjectType(BUTTERFLY);
	this->HP = 1;
}

void Butterfly::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (HP <= 0)
		return;
	Object::Update(deltaTime, objects);


	this->veclocity.y = 0;
	this->veclocity.x = 0;

	this->fly->UpdateSprite();
}

void Butterfly::Render()
{
	if (HP <= 0)
		return;

	Object::Render();
	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (direction == RIGHT)
		this->fly->DrawSprite(pos, false);
	else
		this->fly->DrawSprite(pos, true);
}

void Butterfly::HandleCollision(vector<Object*>* objects)
{
}

void Butterfly::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (HP > 0)
	{
		l = position.x;
		t = position.y;
		r = l + fly->GetWidth();
		b = t + fly->GetHeight();
	}
	else l = r = b = t = 0;
}

void Butterfly::Destroy()
{
}
