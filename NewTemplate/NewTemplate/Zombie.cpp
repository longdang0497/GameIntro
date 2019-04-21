#include "Zombie.h"

Zombie::Zombie(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
}

void Zombie::Update(float deltaTime, std::vector<Object*>* objects)
{
}

void Zombie::Render()
{
}

void Zombie::HandleCollision(vector<Object*>* objects)
{
}

void Zombie::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

void Zombie::Destroy()
{
}
