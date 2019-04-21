#pragma once
#include "Enemy.h"
#include "Define.h"
#include "MainCharacter.h"
#include "ZombieSword.h"

enum ZombieState {
	ZombieWalk,
	ZombieKill
};

class Zombie : public Enemy
{
private:

	/*Sprite * walkSprite;
	Sprite * killSprite;*/

	ZombieState state;

	int spriteDirection;
public:

	Zombie(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2);
	void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();
};