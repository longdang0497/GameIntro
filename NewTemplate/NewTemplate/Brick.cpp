#include "Brick.h"


Brick::Brick(int left, int top, int right, int bottom)
{
	this->SetPosition(left, top);
	this->SetVeclocity(0, 0);
	this->SetBoundingBox(right - left, bottom - top);
	this->SetObjectType(BRICK);
}

Brick::~Brick()
{
}

void Brick::Update(float deltaTime, vector<Object*>* object)
{
}

void Brick::Render()
{

}

