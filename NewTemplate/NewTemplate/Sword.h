#pragma once
#include "Object.h"
#include "MainCharacter.h"
#include "BossBullet.h"
#include "Boss.h"
#include "Explode.h"

class Sword : public Object
{
private:
	bool isActive;

	static Sword* _instance;

	Sprite* swordSprite;

	Explode *explode;
public:
	Sword();
	~Sword();

	void Update(float t, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void CalCulatePosition();

	static Sword* GetInstance() {
		if (_instance == NULL) _instance = new Sword();
		return _instance;
	}

	void GetBoundingBox(float &l, float &t, float &r, float &b);

	void setIsActive(bool a) { this->isActive = a; }

	void checkCollisioWithEnemy(vector<Object*> *coObjects);
};

