#pragma once
#include "Object.h"
#include "Define.h"
#include "MainCharacter.h"
#include "ZombieSword.h"


enum ZombieState {
	ZombieWalk,
	ZombieKill
};

class Zombie : public Object
{
private:

	Sprite * WalkSprite;
	Sprite * KillSprite;

	ZombieState state;

	int spriteDirection;

	int LimitX1, LimitX2;


	ZombieSword* Sword;
public:
	Zombie();
	Zombie(D3DXVECTOR3 pos, int direction);
	Zombie(D3DXVECTOR3 pos, int direction, int MainPos1, int MainPos2);
	~Zombie();


	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);

	void GetBoundingBox(float &l, float &t, float &r, float &b);

};

