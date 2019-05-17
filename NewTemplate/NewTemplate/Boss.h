#pragma once
#include "Object.h"
#include "BossBullet.h"
#include "MainCharacter.h"
#include "BossExplode.h"

#define BOSS_WIDTH 33
#define BOSS_HEIGHT 37
#define FREEZE_TIME 1000
#define HURT_TIME 500


class Boss : public Object
{
private:
	Sprite* boss;
	Sprite* bossJump;
	BossExplode* bossExplode;
	BOSS_STATE bossState;
	DWORD freezeTime;
	DWORD hurtTime;
	int countToShoot;

	vector<BossBullet*> *bullets;

	static Boss* _instance;
public:
	Boss();
	void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();
	vector<BossBullet*>* GetBullets();

	static Boss* GetInstance() {
		if (_instance == NULL) _instance = new Boss();
		return _instance;
	}

	void Hurt();
	DWORD GetHurtTime() { return this->hurtTime; }
};

