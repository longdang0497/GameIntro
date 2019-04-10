#pragma once
#include "Object.h"


class Sword: public Object
{
private:
	bool isActive;

	static Sword* _instance;

	Sprite* swordSprite;
public:
	Sword();
	~Sword();

	void Update(float t, vector<Object*> *object = NULL);
	void Render();

	void CalCulatePosition();

	static Sword* GetInstance() {
		if (_instance == NULL) _instance = new Sword();
		return _instance;
	}

	void GetBoundingBox(float &l, float &t, float &r, float &b);

	void setIsActive(bool a) { this->isActive = a; }

	void checkCollisioWithEnemy(vector<Object*> *coObjects);
};

