#pragma once
#include "Object.h"
#include "Define.h"

class Butterfly : public Object
{
	Sprite * fly;

public:
	Butterfly();
	Butterfly(D3DXVECTOR3 pos, int direction);
	~Butterfly();

	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);

	void GetBoundingBox(float &l, float &t, float &r, float &b);
};


