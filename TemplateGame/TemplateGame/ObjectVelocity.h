#pragma once
#include "ObjectDefine.h"
class ObjectVelocity
{
private:
	float vX;
	float vY;
public:
	ObjectVelocity();
	ObjectVelocity(float vX, float vY);
	~ObjectVelocity();

	void SetVx(float vX);
	void SetVy(float vY);
	float GetVx();
	float GetVy();
};

