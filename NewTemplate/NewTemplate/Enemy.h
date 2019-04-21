#pragma once
#include "Object.h"
#include "Camera.h"

class Enemy : public Object
{
protected:

	int enemyAppearanceDirection;
	int limitX1;
	int limitX2;
	D3DXVECTOR3 defaultPosition;
	int flagAppear = false;
public:
	Enemy(D3DXVECTOR3 pos, int enemyAppearanceDirection, int LimitX1, int LimitX2);
	~Enemy();

	virtual void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	virtual void Render();
	virtual void HandleCollision(vector<Object*> *objects) = 0;
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b) = 0;
	virtual void Destroy() = 0;
};

