#pragma once
#include "Object.h"
#include "Sprite.h"
#include "OtherObjectsDefine.h"

class Brick : public Object
{
private: 
	Sprite *sprite;
	int index;
public:
	Brick();
	Brick(LPD3DXSPRITE spriteHandler, int index, int x, int y);

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void InitPostition();

	void Reset(float  x, float y);
	void Update(float t, vector<Object*> *object = NULL);
	void Render();
	void Destroy();

	bool handleCollision(Object *otherObject);
	~Brick();
};

