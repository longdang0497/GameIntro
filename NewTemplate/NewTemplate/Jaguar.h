#pragma once
#include "Object.h"
#include "Define.h"


class Jaguar : public Object
{
private:

	Sprite * jaguar;

public:
	Jaguar();
	Jaguar(D3DXVECTOR3 position, Direction direction);
	~Jaguar();



	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);
	
	void CheckCollisionWithGround(vector<Object*>* objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);

	
};