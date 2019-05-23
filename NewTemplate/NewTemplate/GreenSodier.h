#pragma once
#include "Enemy.h"
#include "Define.h"
#include "MainCharacter.h"
#include "BazookaBullet.h"

class GreenSodier : public Enemy
{
private:
	Sprite* currentSprite;
	vector<BazookaBullet*> *bullets;
	int state;

	bool isShooting;
	DWORD WaitTime;
	DWORD WaitNext;
	int count;
public:
	~GreenSodier();
	GreenSodier(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2, int state);
	void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();

	void Shoot();

	vector<BazookaBullet*>* GetBullets();
};

