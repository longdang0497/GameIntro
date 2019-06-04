#pragma once
#include "Object.h"

#define TIME_ACTIVE 500

class Explode : public Object
{
private:
	Sprite * sprite;
	int type;
	DWORD activeTime;
public:
	Explode(int type = 1);
	~Explode();

	void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetActive(D3DXVECTOR3 pos);
};

