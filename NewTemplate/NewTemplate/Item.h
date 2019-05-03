#pragma once
#include "Object.h"
#include "Camera.h"

class Item : public Object
{
protected:
	static Item* _instance;
	int strength;
	//D3DXVECTOR3 defaultPosition;
	int flagAppear = false;	
	int objectID;

	Sprite * blueR;
	Sprite * orangeR;
	Sprite * blueDart;
	Sprite * orangeDart;
	Sprite * blueJar;
	Sprite * orangeJar;
	Sprite * bluePocket;
	Sprite * orangePocket;
	Sprite * bigShuriken;
	Sprite * itemFire;
	Sprite * sandglass;
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
	static Item* GetInstance() {
		if (_instance == NULL) _instance = new Item();
		return _instance;
	}

	void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();
};


