#pragma once
#include "Object.h"
#include "Explode.h"
#include "MainCharacter.h"
#include "Camera.h"


class Flames: public Object
{
private:
	static Flames* _instance;
	Explode *explode;
	DWORD StartTime;\

public:
	Flames();
	~Flames();


	static Flames* GetInstance() {
		if (_instance == NULL) _instance = new Flames();
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

