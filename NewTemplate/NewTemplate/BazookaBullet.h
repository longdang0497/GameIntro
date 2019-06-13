#pragma once
#include "Object.h"
#include "Define.h"

class BazookaBullet : public Object
{
private:

	Sprite * bullet;

	int spriteDirection;

	DWORD changeSpriteDirectionTime;
	DWORD WaitTime;
public:
	BazookaBullet();
	BazookaBullet(D3DXVECTOR3 pos, int direction);
	~BazookaBullet();


	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);

	void GetBoundingBox(float &l, float &t, float &r, float &b);

	void SetSpriteDirection(int a) { this->spriteDirection = a; }
	int GetSpriteDirection() { return this->spriteDirection; }
};

