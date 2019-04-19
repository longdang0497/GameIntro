#pragma once
#include "Object.h"
#include "Define.h"
#include "MainCharacter.h"


class ZombieSword : public Object
{
private:

	Sprite * sprite;

	int spriteDirection;

public:
	ZombieSword();
	ZombieSword(D3DXVECTOR3 pos, int direction);
	~ZombieSword();


	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);

	void GetBoundingBox(float &l, float &t, float &r, float &b);

};

