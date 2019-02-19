#include "ObjectVelocity.h"



ObjectVelocity::ObjectVelocity()
{
	this->vx = DEFAULT_VX;
	this->vy = DEFAULT_VY;
}

ObjectVelocity::ObjectVelocity(float vx, float vy)
{
	this->vx = vx;
	this->vy = vy;
}


ObjectVelocity::~ObjectVelocity()
{
}

void ObjectVelocity::SetVx(float vx)
{
	this->vx = vx;
}

void ObjectVelocity::SetVy(float vy)
{
	this->vy = vy;
}

float ObjectVelocity::GetVx()
{
	return this->vx;
}

float ObjectVelocity::GetVy()
{
	return this->vy;
}
