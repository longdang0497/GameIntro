#pragma once
#include <d3dx9.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Define.h"
#include "Game.h"
#include "Camera.h"

using namespace std;

class CollisionEvent;

class Object
{
protected:
	int objectWidth;
	int objectHeight;
	D3DXVECTOR3 position;  // Vị trí hiện tại của object
	D3DXVECTOR3 lastPos;	// Vị trí trước đó của object
	D3DXVECTOR3 veclocity;  // Vận tốc của Object
	OBJECT_TYPE objectType;
	bool isActive;

	// 2 trường này phục vụ cho Grid
	Object* nextObj;
	Object* preObj;

	// Cái này dùng để hỗ trợ cập nhật vị trí của object
	float deltaX;
	float deltaY;
	float deltaTime;

	int direction;

	int enemyAppearanceDirection;

	Sprite* currentSprite;

	bool isOnGround;
	int HP;
public:
	Object();
	~Object();

	//Thuật toán AABB
	bool checkAABB(Object* obj);

	CollisionEvent* SweptAABBEx(Object* coO);


	// Thuật toán SweptAABB
	void SweptAABB(Object* obj, float deltaX, float deltaY, float &collisionTime, float &nx, float& ny);

	// Này dùng để lấy thông số tất cả object có khả năng va chạm với object đang xét
	CollisionEvent* GetCollsionObjectsBySweptAABB(Object* obj);
	void CalcPotentialCollisions(vector<Object*> *objects, vector<CollisionEvent*> *coEvents);
	void FilterCollision(vector<CollisionEvent*> *coEvents, vector<CollisionEvent*> *coEventsResult, float &minTx, float &minTy, float &nx, float &ny);

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b) = 0;
	
	void RenderBoundingBox();

	// Phải update thông tin của Object trước rồi mới render lên lại màn hình
	virtual void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	virtual void Render();
	virtual void HandleCollision(vector<Object*> *objects) = 0;

	D3DXVECTOR3 GetVeclocity() { return this->veclocity; }
	void SetVeclocity(float vx, float vy) {this->veclocity.x = vx;this->veclocity.y = vy;}
	void SetVx(float vx) { this->veclocity.x = vx; }
	void SetVy(float vy) { this->veclocity.y = vy; }

	D3DXVECTOR3 GetPosition() { return this->position; }
	void SetPosition(float x, float y) { this->position.x = x; this->position.y = y; }
	void PlusPosition(float x, float y) { this->position.x += x; this->position.y += y; }

	void SetBoundingBox(int width, int height) { this->objectWidth = width; this->objectHeight = height; }
	void GetObjectBoudingBox(int &width, int &height) { width = this->objectWidth; height = this->objectHeight; }

	void SetObjectType(OBJECT_TYPE objectType) { this->objectType = objectType; }
	OBJECT_TYPE GetObjectType() { return this->objectType; }

	void SetNextObj(Object* obj) { this->nextObj = obj; }
	Object* GetNextObj() { return this->nextObj; }

	void SetPreObj(Object* obj) { this->preObj = obj; }
	Object* GetPreObj() { return this->preObj; }

	void SetLastPos(float x, float y) { this->lastPos.x = x; this->lastPos.y = y; }
	void SetLastPos(D3DXVECTOR3 pos) { this->lastPos.x = pos.x; this->lastPos.y = pos.y; }
	D3DXVECTOR3 GetLastPos() { return this->lastPos; }

	void SetDirection(int a) { this->direction = a; }
	int GetDirection() { return this->direction; }

	void Hurt() { this->HP--; }

	int GetHP() { return this->HP; }
	void SetHP(int value) { this->HP = value; }

	bool GetIsActive() { return this->isActive; }
	void SetIsActive(bool isActive) { this->isActive = isActive; }
};


struct CollisionEvent
{
	Object* obj;
	float t, nx, ny;

	CollisionEvent(float t, float nx, float ny, Object* obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const CollisionEvent* a, CollisionEvent *b)
	{
		return a->t < b->t;
	}
};