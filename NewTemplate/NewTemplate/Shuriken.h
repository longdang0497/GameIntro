#pragma once
#include "Object.h"
#include "Explode.h"
#include "MainCharacter.h"

class Shuriken: public Object
{
private:
	//bool isActive;

	Sprite* ShurikenSprite;

	static Shuriken* _instance;

	Explode *explode;

	int LimitX1, LimitX2,Start;


	DWORD StartTime;
public:
	Shuriken();
	~Shuriken();

	static Shuriken* GetInstance() {
		if (_instance == NULL) _instance = new Shuriken();
		return _instance;
	}

	void Update(float t, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void CalCulatePosition();

	void GetBoundingBox(float &l, float &t, float &r, float &b);

	void setIsActive(bool a) { this->isActive = a; }

	void checkCollisioWithEnemy(vector<Object*> *coObjects);

	void Reset();
};

