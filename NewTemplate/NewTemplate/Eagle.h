#pragma once
#include "Enemy.h"
#include "Define.h"
#include "MainCharacter.h"
#include <ctime>
#include <cstdlib>

#define FREEZE_TIME 190
#define DEFAULT_AMPLITUDE 40

class Eagle : public Enemy
{
private:
	Sprite* sprite;
	D3DXVECTOR3 currentPosition;
	D3DXVECTOR3 lastPosition;
	bool flyingToRight;
	bool flyingToBottom;
	int count;

	int amplitude = DEFAULT_AMPLITUDE;

	bool canAppearAgain = true;
	DWORD lastReachTime = GetTickCount();

public:
	~Eagle();

	Eagle(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2);
	void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();
};

