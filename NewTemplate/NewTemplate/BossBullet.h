#pragma once
#include "Object.h"
#define TIME_TO_MOVE 500

class BossBullet : public Object
{
private:
	Sprite* sprite;
	DWORD freezeTime;
	bool start;
public:
	BossBullet();
	~BossBullet();

	void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();
	void SetStart(D3DXVECTOR3 pos, D3DXVECTOR3 vec);
	bool GetStart() { return this->start; }
};

