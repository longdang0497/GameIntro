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

// Get/set methods
void ObjectPosition::setPosX(float posX)
{
	this->posX = posX;
}

void ObjectPosition::setPosY(float posY)
{
	this->posY = posY;
}

float ObjectPosition::getPosX()
{
	return this->posX;
}

float ObjectPosition::getPosY()
{
	return this->posY;
}

ObjectPosition* ObjectPosition::getPosCenter()
{
	
	float x = (this->posX + this->objectWidth) / 2;
	float y = (this->posY + this->objectHeight) / 2;
	
	this->posCenter = new ObjectPosition(x, y);

	return this->posCenter;
}

void ObjectPosition::setObjectWidth(int width)
{
	this->objectWidth = width;
}

void ObjectPosition::setObjectHeight(int height)
{
	this->objectHeight = height;
}

int ObjectPosition::getObjectWidth()
{
	return this->objectWidth;
}

int ObjectPosition::getObjectHeight()
{
	return this->objectHeight;
}
