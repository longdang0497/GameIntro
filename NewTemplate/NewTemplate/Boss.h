#pragma once
#include "Enemy.h"
#include "BossBullet.h"

#define BOSS_WIDTH 33
#define BOSS_HEIGHT 37
#define FREEZE_TIME 1000


class Boss : public Enemy
{
private:
	Sprite* boss;
	Sprite* bossJump;

	BOSS_STATE bossState;

	DWORD freezeTime;

	int countToShoot;

	vector<BossBullet*> *bullets;
public:
	Boss(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2);
	void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();
	vector<BossBullet*>* GetBullets();
};

