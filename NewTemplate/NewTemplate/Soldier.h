#pragma once
#include "Object.h"
#include "Define.h"
#include "MainCharacter.h"

enum Soldier_State {
	Walk,
	Kill
};


class Soldier : public Object
{
	Sprite * SoldierWalk;
	Sprite * SoldierKill;

	Soldier_State state;

	int LimitX1, LimitX2;

public:
	Soldier();
	Soldier(D3DXVECTOR3 pos, int direction);
	Soldier(D3DXVECTOR3 pos, int direction, int LimitX1, int LimitX2);
	~Soldier();

	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);

	void GetBoundingBox(float &l, float &t, float &r, float &b);
};

