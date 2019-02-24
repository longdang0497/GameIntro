#pragma once
#include "Object.h"
#include "ObjectDefine.h"
#include "Sprite.h"
#include "trace.h"
#include <vector>

class MainCharacter : public Object
{
protected:
	MAIN_CHARACTER_MOVEMENT state;
	Sprite * stand_right;
	Sprite * stand_left;
	Sprite * run_right;
	Sprite * run_left;

	bool isCollided = false;
public:
	MainCharacter();
	MainCharacter(LPD3DXSPRITE spriteHandler);
	~MainCharacter();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void InitPostition();

	MAIN_CHARACTER_MOVEMENT GetState();
	void SetState(MAIN_CHARACTER_MOVEMENT value);

	void ResetAllSprites();
	bool GetStateActive();

	void Reset(float  x, float y);
	void Update(float t);
	void Render();
	void Destroy();

	bool handleCollision(Object *otherObject);
};