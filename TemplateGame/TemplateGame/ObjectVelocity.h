#pragma once
#include "ObjectDefine.h"
class ObjectVelocity
{
private:
	float vx;
	float vy;
public:
	ObjectVelocity();
	ObjectVelocity(float vx, float vy);
	~ObjectVelocity();

	void setVx(float vx);
	void setVy(float vy);
	float getVx();
	float getVy();
};

