#include "Eagle.h"

Eagle::~Eagle()
{
}

Eagle::Eagle(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->SetObjectType(EAGLE);
	this->HP = 1;
}

void Eagle::Update(float deltaTime, std::vector<Object*>* objects)
{
}

void Eagle::Render()
{
}

void Eagle::HandleCollision(vector<Object*>* objects)
{
}

void Eagle::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

void Eagle::Destroy()
{
}
