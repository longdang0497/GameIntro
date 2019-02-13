#include "ObjectVelocity.h"



ObjectVelocity::ObjectVelocity()
{
	this->vX = DEFAULT_VX;
	this->vY = DEFAULT_VY;
}

ObjectVelocity::ObjectVelocity(float vX, float vY)
{
	this->vX = vX;
	this->vY = vY;
}


ObjectVelocity::~ObjectVelocity()
{
}

void ObjectVelocity::SetVx(float vX)
{
	this->vX = vX;
}

void ObjectVelocity::SetVy(float vY)
{
	this->vY = vY;
}

float ObjectVelocity::GetVx()
{
	return this->vX;
}

float ObjectVelocity::GetVy()
{
	return this->vY;
}
