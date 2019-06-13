#pragma once
#include "Object.h"
#include "Camera.h"

class Item : public Object
{
protected:
	//static Item* _instance;
	int strength;
	int alpha = 255;	// Sử dụng khi item hết thời gian hiển thị
	//D3DXVECTOR3 defaultPosition;
	int flagAppear = false;	
	int objectID;
	float timeAppear = 0;


public:
	Item();
	Item(D3DXVECTOR3 pos, int objectID);
	~Item();

	void InitItemSprite();

	int GetObjID() { return this->objectID; }
	void SetObjID(int value);

	int GetStrength() { return this->strength; }
	void SetStrength(int value) { this->strength = value; }

	/*D3DXVECTOR3 GetPosition() { return this->defaultPosition; }
	void SetPo(D3DXVECTOR3 value) { this->strength = value; }*/
	//static Item* GetInstance() {
	//	if (_instance == NULL) _instance = new Item();
	//	return _instance;
	//}

	//void SetTimeAppear() { this->startAppear = GetTickCount(); }

	void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();

};


