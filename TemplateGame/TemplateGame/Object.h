#pragma once
#include "ObjectPosition.h"
#include "ObjectVelocity.h"
#include <d3dx9.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class CollisionEvent;

class Object
{
protected:
	int objectWidth;		
	int objectHeight;
	ObjectPosition *curPos;			// Vị trí hiện tại của object
	ObjectPosition *lastPos;			// Vị trí trước đó của object
	float gravity;
	float friction;
	Object *nextObject;		// Phục vụ cho Grid, xác định con trỏ tiếp theo của object là ai
	Object *preObject;		// Phục vụ cho Grid, xác định con trỏ trc đó của object là ai
	ObjectVelocity *curVec;			// Vận tốc hiện tại của object
	ObjectVelocity *lastVec;		// Vận tốc gần nhất của object
	OBJECT_TYPE objectType;
	LPD3DXSPRITE spriteHandler;		// Cái này dùng để vẽ Sprite nè
	bool isActive;					// Biến để xác định Object có đang hoạt động hay không
	DWORD lastTime;					// Cái này để điều khiển được tỉ lệ animate của object
	D3DXVECTOR2 rigidBody;			// Cái này đùng để điều khiển camera

	float deltaPosX;
	float deltaPosY;
	DWORD deltaTime;

public:
	Object();
	~Object();

	float GetCollisionTime(Object* otherObject, COLLISION_DIRECTION& collisionDirection, float deltaTime);

	// Này là thuật toán sweptAABB
	void SweptAABB(Object* otherObject, float dx, float dy, float &t, float &nx, float &ny);
	
	// Này dùng để lấy thông số tất cả object có khả năng va chạm với object đang xét
	CollisionEvent* GetCollsionObjectsBySweptAABB(Object* obj);
	void CalcPotentialCollisions(vector<Object*> *objects, vector<CollisionEvent*> *coEvents);
	void FilterCollision(vector<CollisionEvent*> *coEvents, vector<CollisionEvent*> *coEventsResult, float &minTx, float &minTy, float &nx, float &ny);

	RECT* GetBoundingBox();

	// Phương thức để active lại GameObject
	virtual void Init(float posX, float posY);

	// Khởi tạo Sprite cho Object
	virtual void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture) = 0;

	// Phải update thông tin của Object trước rồi mới render lên lại màn hình
	virtual void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	virtual void Render() = 0;

	// Phương thức này được hiểu theo nghĩa là khi object đã chết (tức là chỉ có làm cho isActive là false thôi chứ k xóa khỏi bộ nhớ)
	virtual void Destroy() = 0;

	// Phương thức này dùng để xử lý va chạm giữa các Object với nhau
	virtual bool handleCollision(Object *otherObject) = 0;

	void SetPosition(float posX, float posY);
	void SetVeclocity(float vX, float vY);

	void SetObjectType(OBJECT_TYPE objectType);
	void SetIsActive(bool isActive);
	void SetCurPosition(ObjectPosition *curPos);
	void SetLastPosition(ObjectPosition *lastPos);
	void SetCurVec(ObjectVelocity *curVec);
	void SetLastVec(ObjectVelocity *lastVec);
	void SetNextObject(Object* nextObject);
	void SetPreObject(Object* preObject);
	void SetObjectWidth(int width);
	void SetObjectHeight(int height);
	void SetGravity(float gravity);
	void SetSpriteHandler(LPD3DXSPRITE spriteHandler);

	OBJECT_TYPE GetObjectType();
	bool GetIsActive();
	ObjectPosition* GetCurPos();
	ObjectPosition* GetLastPos();
	ObjectVelocity* GetCurVec();
	ObjectVelocity* GetLastVec();
	Object* GetNextObject();
	Object* GetPreObject();
	int GetObjectWidth();
	int GetObjectHeight();
	float GetGravity();
	LPD3DXSPRITE GetSpriteHandler();
};

// Class này quản lý các vật có khả năng va chạm với Object đang xét
// Thông số nx, ny này dùng để xác định đc phần nào va chạm trc rồi lùi cái frame lại cho nó khỏi bị chồng lên nhau (nếu trường hợp xét khi di chuyển)
class CollisionEvent
{
private:
	Object* obj;
	float collisionTime, nx, ny;
public:
	CollisionEvent(float collisionTime, float nx, float ny, Object* obj = NULL);
	~CollisionEvent();

	static bool Compare(const CollisionEvent* a, const CollisionEvent *b) {
		return a->collisionTime < b->collisionTime;
	}

	float GetCollisionTime() {
		return this->collisionTime;
	}

	float GetNx() {
		return this->nx;
	}

	float GetNy() {
		return this->ny;
	}
};
