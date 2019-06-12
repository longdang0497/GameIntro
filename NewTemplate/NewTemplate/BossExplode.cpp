#include "BossExplode.h"



BossExplode::BossExplode()
{
	this->sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_BOSS_EXPLODE);
	this->isActive = false;
	this->timeActive = GetTickCount();
}


BossExplode::~BossExplode()
{
	if (this->sprite != NULL) delete this->sprite;
}

void BossExplode::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (!this->isActive) {
		return;
	}

	if (GetTickCount() - this->timeActive > ACTIVE_TIME) {
		this->isActive = false;
		return;
	}

	this->sprite->UpdateSprite();
}

void BossExplode::Render()
{
	if (!this->isActive) return;

	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (this->sprite->GetIndex() == 1) {
		this->sprite->DrawSprite({pos.x - 8, pos.y - 8, 0}, true, 128);
	}
	else {
		this->sprite->DrawSprite(pos, true, 128);
	}

}

void BossExplode::HandleCollision(vector<Object*>* objects)
{
}

void BossExplode::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

void BossExplode::SetActive(D3DXVECTOR3 pos)
{
	this->SetPosition(pos.x, pos.y);
	this->isActive = true;
	this->timeActive = GetTickCount();
}
