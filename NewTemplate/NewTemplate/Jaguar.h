#pragma once
#include "Object.h"
#include "Define.h"
#include "MainCharacter.h"


class Jaguar : public Object
{
private:

	Sprite * jaguar;

	int MainPos1, MainPos2;
	D3DXVECTOR3 defaultPosition;

public:
	Jaguar();
	Jaguar(D3DXVECTOR3 pos, int direction);
	Jaguar(D3DXVECTOR3 pos, int direction, int MainPos1, int MainPos2);
	~Jaguar();


	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);

	void GetBoundingBox(float &l, float &t, float &r, float &b);

};