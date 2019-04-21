#include "Soldier.h"

Soldier::Soldier(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
}

void Soldier::Update(float deltaTime, std::vector<Object*>* objects)
{
}

void Soldier::Render()
{
}

void Soldier::HandleCollision(vector<Object*>* objects)
{
}

void Soldier::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

void Soldier::Destroy()
{
}
