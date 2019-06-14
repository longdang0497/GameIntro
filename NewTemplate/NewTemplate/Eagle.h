#pragma once
#include "Enemy.h"
#include "Define.h"
#include "MainCharacter.h"
#include "Graphic.h"
#include <ctime>
#include <cstdlib>

#define EAGLE_VEC_X 0.13f
#define EAGLE_HIGHTEST_POS_Y 160.0f
#define EAGLE_LOWEST_POS_Y 190.0f
#define EAGLE_FREEZE_TIME 200
#define EAGLE_HIGHTER_LIMIT 50
#define EAGLE_LOWER_LIMIT 70

class Eagle : public Enemy
{
private:
	Sprite *sprite;
	
	int count;	// count này dùng để xác định và tính toán các vị trí tiếp theo của đại bàng

	bool canAppearAgain;

	bool flyingToRight;
	bool flyingToBottom;

	DWORD  lastReachTime;

	D3DXVECTOR3 currentPos;
	D3DXVECTOR3 lastPos;

	bool CheckCurrentPosAndPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float min, float max);

public:
	~Eagle();

	Eagle(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2);
	void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();
};

