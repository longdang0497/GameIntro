#include "ZombieSword.h"

ZombieSword::ZombieSword()
{
	this->sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_ZOMBIES_SWORD);
	this->SetObjectType(ZOMBIE_SWORD);
	this->HP = 1;
	direction = LEFT;
	spriteDirection = RIGHT;
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
	spriteDirection = LEFT;
	changeSpriteDirectionTime = GetTickCount();
}


void ZombieSword::Update(float deltaTime, vector<Object*>* object)
{
	if (HP <= 0)
		return;
	Object::Update(deltaTime, object);
	
	//if (changeSpriteDirectionTime - GetTickCount() >= 1000)
	//{
	//	if (spriteDirection == LEFT)
	//		spriteDirection = RIGHT;
	//	else
	//		spriteDirection = LEFT;

	//	changeSpriteDirectionTime = GetTickCount();
	//}

	this->veclocity.y += 0;// 0.00005f*deltaTime;

	this->veclocity.x = 0*direction;

	this->currentSprite->UpdateSprite();

	this->PlusPosition(this->deltaX, this->deltaY);
}

void ZombieSword::Render()
{
	if (HP <= 0)
		return;

	Object::Render();
	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (spriteDirection == LEFT)
		this->currentSprite->DrawSprite(pos, false);
	else
		this->currentSprite->DrawSprite(pos, true);
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