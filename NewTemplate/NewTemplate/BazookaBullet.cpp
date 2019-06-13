#include "BazookaBullet.h"
#include "MainCharacter.h"

BazookaBullet::BazookaBullet()
{
	this->bullet = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_BAZOOKA_BULLET);
	this->SetObjectType(BAZOOKA_BULLET);
	this->HP = 1;

	direction = LEFT;
	spriteDirection = RIGHT;
	isActive = false;
	changeSpriteDirectionTime = GetTickCount();
	WaitTime = GetTickCount();
}

BazookaBullet::~BazookaBullet()
{
	if (this->bullet != NULL) delete this->bullet;
}

BazookaBullet::BazookaBullet(D3DXVECTOR3 pos, int direction)
{
	this->bullet = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_BAZOOKA_BULLET);
	this->SetObjectType(BAZOOKA_BULLET);
	this->HP = 1;
	isActive = false;
	//direction = LEFT;

	//this->SetPosition(pos.x, pos.y);
	this->direction = direction;
	spriteDirection = direction;
	changeSpriteDirectionTime = GetTickCount();
}


void BazookaBullet::Update(float deltaTime, vector<Object*>* object)
{
	if (this->isActive == true)
	{
		if (HP <= 0)
			return;

		if (MainCharacter::GetInstance()->IsStopWatch())
			return;

		Object::Update(deltaTime, object);

		DWORD temp = GetTickCount() - WaitTime;
		if (temp >= 15000)
		{
			//this->isActive = false;
			this->HP = 0;
		}

		//this->veclocity.x = 0.1f*direction;
		//this->veclocity.y = 0;
		
		this->PlusPosition(deltaX, deltaY);

		this->bullet->UpdateSprite();
	}
}

void BazookaBullet::Render()
{
	if (isActive == false || HP <= 0)
		return;

	Object::Render();
	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (spriteDirection == LEFT)
		this->bullet->DrawSprite(pos, false);
	else
		this->bullet->DrawSprite(pos, true);
}

void BazookaBullet::HandleCollision(vector<Object*>* objects)
{

}

void BazookaBullet::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (HP > 0)
	{
		l = position.x;
		t = position.y;
		r = l + bullet->GetWidth();
		b = t + bullet->GetHeight();
	}
	else l = r = b = t = 0;
}