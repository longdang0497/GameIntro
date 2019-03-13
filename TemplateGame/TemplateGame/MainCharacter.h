#pragma once
#include "Object.h"
#include "ObjectDefine.h"
#include "Sprite.h"
#include "trace.h"
#include <vector>

class MainCharacter : public Object
{
private:
	MAIN_CHARACTER_STATE state;
	Sprite * standSprite;
	Sprite * runSprite;

	bool isCollided = false;
public:
	MainCharacter();
	MainCharacter(LPD3DXSPRITE spriteHandler);
	~MainCharacter();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void InitPostition();

	MAIN_CHARACTER_STATE GetState();
	void SetState(MAIN_CHARACTER_STATE value);

	void ResetAllSprites();
	bool GetStateActive();

	void Reset(float  x, float y);
	void Update(float t, vector<Object*> *object = NULL);
	void Render();
	void Destroy();

	bool handleCollision(Object *otherObject);
};