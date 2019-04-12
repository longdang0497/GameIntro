#include "Ladder.h"


Ladder::Ladder(int left, int top, int right, int bottom)
{
	this->SetPosition(left, top);
	this->SetVeclocity(0, 0);
	objectHeight = bottom - top;
	objectWidth = right - left;
	this->SetObjectType(LADDER);
}

Ladder::~Ladder()
{
}

void Ladder::Update(float deltaTime, vector<Object*>* object)
{
}

void Ladder::Render()
{
	RenderBoundingBox();
}

void Ladder::HandleCollision(vector<Object*>* objects)
{
}

void Ladder::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = position.x;
	t = position.y;
	r = l + objectWidth;
	b = t + objectHeight;
}

