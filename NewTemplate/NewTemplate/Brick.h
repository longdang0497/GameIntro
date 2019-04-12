#pragma once
#include "Object.h"
#include "Define.h"
class Brick : public Object
{
private:
	
public:
	Brick(int left, int top, int right, int bottom);
	~Brick();

	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};

