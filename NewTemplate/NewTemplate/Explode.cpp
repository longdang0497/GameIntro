#include "Explode.h"



Explode::Explode()
{
	this->sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_EXPLODE);
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

	if (GetTickCount() - this->activeTime >= TIME_ACTIVE) {
		this->isActive = false;
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
	 
	this->sprite->DrawSprite(pos, true, 128);
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