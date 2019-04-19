#include "Brick.h"


Brick::Brick(int left, int top, int right, int bottom, int canStick)
{
	this->SetPosition(left, top);
	this->SetVeclocity(0, 0);
	objectHeight = bottom - top;
	objectWidth = right - left;
	this->SetObjectType(BRICK);
	HP = 1;
	this->canStick = canStick;
}

Brick::~Brick()
{
}

void Brick::Update(float deltaTime, vector<Object*>* object)
{
}

void Brick::Render()
{
	Object::Render();
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

