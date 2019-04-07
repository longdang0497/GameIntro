#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Object.h"
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "Grid.h"
#include "MainCharacter.h"
#include "Define.h"
#include "Grid.h"
class Stage
{
protected:
	vector<Object*> *objects;
	vector<RECT> *bricks;
public:
	Stage();
	~Stage();

	// Dùng để cắt theo hàng ngang
	void InitBrick(RECT rect);

	// Dùng để cắt theo hàng dọc
	void InitBrick1(RECT rect);

	virtual void LoadResource() = 0;
	virtual void Update(float deltaTime);
	virtual void Render();
};