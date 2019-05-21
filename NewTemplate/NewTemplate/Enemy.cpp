#include "Enemy.h"




Enemy::Enemy(D3DXVECTOR3 pos, int enemyAppearanceDirection, int LimitX1, int LimitX2)
{
	this->enemyAppearanceDirection = enemyAppearanceDirection;
	this->limitX1 = LimitX1;
	this->limitX2 = LimitX2;
	this->defaultPosition = pos;
	this->position = pos;
	this->veclocity = { 0,0,0 };
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime, std::vector<Object*>* objects)
{
}

void Enemy::Render()
{
}

bool Enemy::IsInCamera(float x, float y)
{

	if (x >= MainCharacter::GetInstance()->GetPosition().x - 128 && x <= x >= MainCharacter::GetInstance()->GetPosition().x - 128
		&& y >= 0 && y <= Graphic::GetInstance(NULL, NULL, L"", 1)->GetHeight()) {
		return true;
	}

	return false;
}
