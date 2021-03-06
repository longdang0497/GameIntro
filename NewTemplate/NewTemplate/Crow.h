#pragma once
#include "Enemy.h"
#include "Define.h"
#include "Item.h"

class Crow : public Enemy
{
private:
	Sprite * fly;
	int itemId;
	Item * item;
	bool firstCreate = false;
public:
	Crow(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2);
	~Crow();
	void Update(float deltaTime, std::vector<Object*> *objects = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();

	void ActivateItem();
	Item * GetItem() { return this->item; }

	int GetItemId() { return this->itemId; }
};
