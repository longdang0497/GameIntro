#include "ObjectPosition.h"



ObjectPosition::ObjectPosition()
{
	this->posX = DEFAULT_POS_X;
	this->posY = DEFAULT_POS_Y;
	this->objectWidth = DEFAULT_OBJECT_WIDTH;
	this->objectHeight = DEFAULT_OBJECT_HEIGHT;
}

ObjectPosition::ObjectPosition(float postX, float posY, int width, int height )
{
	this->posX = postX;
	this->posY = posY;
	this->objectWidth = width;
	this->objectHeight = height;
}


ObjectPosition::~ObjectPosition()
{
}

RECT * ObjectPosition::GetBoudingBox()
{
	RECT* rect = new RECT();

	rect->top = posY;
	rect->left = posX;
	rect->bottom = posY + objectHeight;
	rect->right = posX + objectWidth;

	return rect;
}

// Get/Set methods
void ObjectPosition::SetPosX(float posX)
{
	this->posX = posX;
}

void ObjectPosition::SetPosY(float posY)
{
	this->posY = posY;
}

void ObjectPosition::Add(float deltaX, float deltaY)
{
	this->posX += deltaX;
	this->posY += deltaY;
}

float ObjectPosition::GetPosX()
{
	return this->posX;
}

float ObjectPosition::GetPosY()
{
	return this->posY;
}

ObjectPosition* ObjectPosition::GetPosCenter()
{
	
	float x = (this->posX + this->objectWidth) / 2;
	float y = (this->posY + this->objectHeight) / 2;
	
	this->posCenter = new ObjectPosition(x, y);

	return this->posCenter;
}

void ObjectPosition::SetObjectWidth(int width)
{
	this->objectWidth = width;
}

void ObjectPosition::SetObjectHeight(int height)
{
	this->objectHeight = height;
}

int ObjectPosition::GetObjectWidth()
{
	return this->objectWidth;
}

int ObjectPosition::GetObjectHeight()
{
	return this->objectHeight;
}
