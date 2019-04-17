#pragma once
#include "Object.h"
#include "Define.h"
#include "Brick.h"
#include "MainCharacter.h"

class Jaguar : public Object
{
private:
	static Jaguar* _instance;
	JAGUARS_STATE state;

	Sprite * jaguar;

	bool isActive;
	bool isOnGround;
	int score;
	float gravity;
public:
	Jaguar();
	~Jaguar();

	void InitJaguarInfo();

	JAGUARS_STATE GetState();
	void SetState(JAGUARS_STATE value);

	bool GetIsActive() { return this->isActive; }
	void SetIsActive(bool value) { this->isActive = value; }

	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void CheckCollisionWithGround(Brick *brick);
	void CheckCollisionWithMain(MainCharacter *main);
	void GetBoundingBox(float &l, float &t, float &r, float &b);

	static Jaguar* GetInstance() {
		if (_instance == NULL) _instance = new Jaguar();
		return _instance;
	}
};