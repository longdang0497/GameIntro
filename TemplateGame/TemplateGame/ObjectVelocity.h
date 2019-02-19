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

	void SetVx(float vx);
	void SetVy(float vy);
	float GetVx();
	float GetVy();
};

