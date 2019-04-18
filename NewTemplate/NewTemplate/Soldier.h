#pragma once
#include "Object.h"
#include "Define.h"
#include "MainCharacter.h"

enum Soldier_State {
	State_Walk,
	State_Kill
};

class Soldier: public Object
{
private:

	Sprite * walk;
	Sprite* kill;

	Soldier_State state;

public:
	Soldier();
	Soldier(D3DXVECTOR3 position, Direction direction);
	~Soldier();



	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *objects);

	void CheckCollisionWithGround(vector<Object*>* objects);
	void GetBoundingBox(float &l, float &t, float &r, float &b);


	void SetState(Soldier_State s);
	Soldier_State GetState() { return this->state; }


};
