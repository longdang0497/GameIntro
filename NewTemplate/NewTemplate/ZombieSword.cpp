#include "ZombieSword.h"

ZombieSword::ZombieSword()
{
	this->sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_ZOMBIES_SWORD);
	this->SetObjectType(ZOMBIE_SWORD);
	this->HP = 1;
	direction = LEFT;
	spriteDirection = LEFT;
	currentSprite = sprite;
}

ZombieSword::~ZombieSword()
{
	if (this->sprite != NULL) delete this->sprite;
}

ZombieSword::ZombieSword(D3DXVECTOR3 pos, int direction)
{
	this->sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_ZOMBIES_SWORD);
	this->SetObjectType(ZOMBIE_SWORD);
	this->HP = 1;
	direction = LEFT;
	currentSprite = sprite;

	this->position = pos;
	this->direction = direction;
	spriteDirection = direction;

}


void ZombieSword::Update(float deltaTime, vector<Object*>* object)
{
	if (HP <= 0)
		return;
	Object::Update(deltaTime, object);

	spriteDirection *= -1;

	this->veclocity.y += 0.0015f*deltaTime;

	this->veclocity.x = 0.1f*direction;

	this->currentSprite->UpdateSprite();

}

void ZombieSword::Render()
{
	if (HP <= 0)
		return;

	Object::Render();
	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (this->spriteDirection == RIGHT)
		this->currentSprite->DrawSprite(pos, true);
	else
		this->currentSprite->DrawSprite(pos, false);
}

void ZombieSword::HandleCollision(vector<Object*>* objects)
{

}



void ZombieSword::GetBoundingBox(float &l, float &t, float &r, float &b)
{

	if (HP > 0)
	{
		l = position.x;
		t = position.y;
		r = l + currentSprite->GetWidth();
		b = t + currentSprite->GetHeight();
	}
	else l = r = b = t = 0;
}