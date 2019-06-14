#include "HideObject.h"



HideObject::HideObject()
{
}


HideObject::~HideObject()
{
}

HideObject::HideObject(int left, int top, int right, int bottom, HIDE_OBJECT_TYPE objecttype)
{
	this->SetPosition(left, top);
	this->SetVeclocity(0, 0);
	objectHeight = bottom - top;
	objectWidth = right - left;
	this->isActive = true;
	this->SetObjectType(HIDE_OBJECT);
	this->type = objecttype;
}



void HideObject::Update(float deltaTime, vector<Object*>* object)
{

}

void HideObject::Render()
{
	Object::Render();
}

void HideObject::HandleCollision(vector<Object*>* objects)
{
}

void HideObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x;
	t = position.y;
	r = l + objectWidth;
	b = t + objectHeight;
}

float HideObject::GetBottom()
{
	return this->position.y  + objectHeight;
}

float HideObject::GetTop()
{
	return this->position.y;
}


