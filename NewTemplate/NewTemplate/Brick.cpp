#include "Brick.h"


Brick::Brick(int left, int top, int right, int bottom)
{
	this->SetPosition(left, top);
	this->SetVeclocity(0, 0);
	objectHeight = bottom - top;
	objectWidth = right - left;
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
	RenderBoundingBox();
	int i = 1;
}

void Brick::HandleCollision(vector<Object*>* objects)
{
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = position.x;
	t = position.y;
	r = l + objectWidth;
	b = t + objectHeight;
}

