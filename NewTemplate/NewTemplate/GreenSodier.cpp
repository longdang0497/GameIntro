#include "GreenSodier.h"

GreenSodier::GreenSodier(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	
}

GreenSodier::~GreenSodier()
{
}



void GreenSodier::Update(float deltaTime, std::vector<Object*>* objects)
{
}

void GreenSodier::Render()
{
}

void GreenSodier::HandleCollision(vector<Object*>* objects)
{
}

void GreenSodier::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

void GreenSodier::Destroy()
{
}
