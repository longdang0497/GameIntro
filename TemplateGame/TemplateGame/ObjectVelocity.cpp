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

void ObjectVelocity::setVx(float vx)
{
	this->vx = vx;
}

void ObjectVelocity::setVy(float vy)
{
	this->vy = vy;
}

float ObjectVelocity::getVx()
{
	return this->vx;
}

float ObjectVelocity::getVy()
{
	return this->vy;
}
