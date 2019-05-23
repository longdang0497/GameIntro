#pragma once
#include "Enemy.h"
#include "Define.h"
#include "MainCharacter.h"

enum Soldier_State {
	Sodier_Walk,
	Sodier_Kill
};

class Soldier : public Enemy
{
private:
	Sprite * SoldierWalk;
	Sprite * SoldierKill;


	Soldier_State state;

public:
	Soldier(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2);
	void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();
};

