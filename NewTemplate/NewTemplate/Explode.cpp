#include "Explode.h"



Explode::Explode(int type)
{
	this->type = type;
	if(type==1)
		this->sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_EXPLODE1);
	else
		this->sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_EXPLODE2);
	this->isActive = false;
	this->SetPosition(100, 100);
	this->SetVeclocity(0, 0);
}


Explode::~Explode()
{
	if (this->sprite != NULL) delete this->sprite;
}

void Explode::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (!this->isActive) {
		return;
	}

	sprite->UpdateSprite();

	//if (GetTickCount() - this->activeTime >= TIME_ACTIVE) {
	//	this->isActive = false;
	//	return;
	//}

	if (sprite->getDone())
	{
		this->isActive = false;
		sprite->setDone(false);
		return;
	}
}

void Explode::Render()
{
	if (!this->isActive) {
		return;
	}

	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);
	 
	this->sprite->DrawSprite(pos, false);
}

void Explode::HandleCollision(vector<Object*>* objects)
{
}

void Explode::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

void Explode::SetActive(D3DXVECTOR3 pos) {
	this->SetPosition(pos.x, pos.y);
	this->isActive = true;
	this->activeTime = GetTickCount();
}