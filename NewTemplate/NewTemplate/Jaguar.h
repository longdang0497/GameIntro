#pragma once
#include "Object.h"
#include "Define.h"

class Jaguar : public Object
{
private:
	static Jaguar* _instance;
	JAGUARS_STATE state;

	Sprite * jaguar;

	int score;
public:
	Jaguar();
	~Jaguar();

	JAGUARS_STATE GetState();
	void SetState(JAGUARS_STATE value);

	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};