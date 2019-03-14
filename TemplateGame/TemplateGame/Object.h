#pragma once
#include "ObjectPosition.h"
#include "ObjectVelocity.h"
#include <d3dx9.h>
#include <iostream>
#include "CSprites.h"

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
	vector<LPANIMATION> animations;
public:
	Object();
	~Object();

	float GetCollisionTime(Object* otherObject, COLLISION_DIRECTION& collisionDirection, float deltaTime);
	RECT* GetBoundingBox();

	// Phương thức để active lại GameObject
	virtual void Init(float posX, float posY);

	// Khởi tạo Sprite cho Object
	//virtual void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture) = 0;

	// Phải update thông tin của Object trước rồi mới render lên lại màn hình
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;

	// Phương thức này được hiểu theo nghĩa là khi object đã chết (tức là chỉ có làm cho isActive là false thôi chứ k xóa khỏi bộ nhớ)
	virtual void Destroy() = 0;

	// Phương thức này dùng để xử lý va chạm giữa các Object với nhau
	virtual bool handleCollision(Object *otherObject) = 0;

	void AddAnimation(int aniId);

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

