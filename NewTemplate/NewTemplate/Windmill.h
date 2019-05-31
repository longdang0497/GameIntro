#pragma once
#include "Object.h"
#include "Explode.h"
#include "MainCharacter.h"
#include "Camera.h"

class Windmill: public Object
{
private:
	//bool isActive;

	Sprite*WindmillSprite;

	static Windmill* _instance;

	Explode *explode;

	int LimitX1, LimitX2, Start, LimitY1, LimitY2, NumOfChangeDirection;
	int nY;

	DWORD StartTime;
public:
	Windmill();
	~Windmill();

	static Windmill* GetInstance() {
		if (_instance == NULL) _instance = new Windmill();
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

