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
class Stage
{
protected:
	vector<Object*> *objects;
public:
	Stage();
	~Stage();

	virtual void LoadResource() = 0;
	virtual void Update(float deltaTime);
	virtual void Render();
};