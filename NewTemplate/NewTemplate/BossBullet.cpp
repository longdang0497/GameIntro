#include "BossBullet.h"



BossBullet::BossBullet()
{
	this->sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_BOSS_BULLET);
	this->HP = 1;
	this->isActive = false;
	this->freezeTime = GetTickCount();
	this->SetObjectType(BOSS_BULLET);
	this->SetPosition(0, 0);
	this->SetVeclocity(0, 0);
	this->start = true;
	this->explode = new Explode();
}


BossBullet::~BossBullet()
{

}

void BossBullet::Update(float deltaTime, std::vector<Object*>* objects)
{
	this->explode->Update(deltaTime, objects);
	if (this->HP < 0 || !this->isActive) {
		return;
	}

	if (this->position.x < 26 || this->position.x > 224) {
		this->isActive = false;
		this->start = false;
		return;
	}

	this->position.x += this->veclocity.x*deltaTime;
	
}

void BossBullet::Render()
{
	this->explode->Render();
	if (!this->isActive) {
		return;
	}

	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	this->sprite->DrawSprite(pos, true);
}

void BossBullet::HandleCollision(vector<Object*>* objects)
{
}

void BossBullet::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (this->HP > 0) {
		this->objectWidth = this->sprite->GetWidth();
		this->objectHeight = this->sprite->GetHeight();
		l = this->position.x;
		t = this->position.y;
		r = l + objectWidth;
		b = t + objectHeight;
	}
	else
		l = t = r = b = 0;
}

void BossBullet::Destroy() {
	this->HP = 0;
	this->isActive = false;
	this->start = false;
	float x, y;
	x = this->position.x - 15;
	y = this->position.y - 19;
	this->explode->SetActive(D3DXVECTOR3(x, y, 0));
	this->SetPosition(0, 0);
}

void BossBullet::SetStart(D3DXVECTOR3 pos, D3DXVECTOR3 vec) {
	this->SetPosition(pos.x, pos.y);
	this->SetVeclocity(vec.x, vec.y);
	this->start = true;
	this->HP = 1;
	this->freezeTime = GetTickCount();
}