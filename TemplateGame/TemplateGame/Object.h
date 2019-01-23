#pragma once
#include "ObjectPosition.h"
#include "ObjectVelocity.h"
#include <d3dx9.h>
#include <iostream>

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
	D3DXVECTOR2 rigidBody;			// TODO: Cái này thì chưa biết làm gì

public:
	Object();
	~Object();

	float GetCollisionTime(Object* otherObject, COLLISION_DIRECTION& collisionDirection, float deltaTime);

	virtual void InitSprites();

	// Phải update thông tin của Object trước rồi mới render lên lại màn hình
	virtual void Update(float deltaTime);
	virtual void Render();

	// Phương thức để active lại GameObject
	virtual void Init(float posX, float posY);

	// Phương thức này được hiểu theo nghĩa là khi object đã chết (tức là chỉ có làm cho isActive là false thôi chứ k xóa khỏi bộ nhớ)
	virtual void Destroy();

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

