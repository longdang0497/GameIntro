#pragma once
#include "Define.h"
#include "Object.h"

class HideObject:public Object
{
private:
	HIDE_OBJECT_TYPE type;
public:
	HideObject();
	HideObject(int left, int top, int right, int bottom, HIDE_OBJECT_TYPE objType);
	~HideObject();

	void Update(float deltaTime, vector<Object*>* object = NULL);
	void Render();
	void HandleCollision(vector<Object*>* objects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	HIDE_OBJECT_TYPE getType() { return this->type; }
	
};

