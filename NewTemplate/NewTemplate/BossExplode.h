#pragma once
#include "Object.h"

#define ACTIVE_TIME 4000
class BossExplode : Object
{
private:
	Sprite *sprite;
	DWORD timeActive;
public:
	BossExplode();
	~BossExplode();

	void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetActive(D3DXVECTOR3 pos);
};

