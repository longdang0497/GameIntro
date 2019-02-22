#pragma once
#include "Grid.h"
#include "DXGraphics.h"
#include "Texture.h"
#include "MainCharacter.h"

// Class này dùng để quản lý các object của thế giới Game
// Bao gồm Map, Sprite, Main, Enemy, Grid, ...
class World
{
private:
	Grid* grid;
	LPD3DXSPRITE spriteHandler;
	Texture* texture;
	MainCharacter * gameCharacter;

	void LoadResources(LPDIRECT3DDEVICE9);
	void InitSprite(LPDIRECT3DDEVICE9);
	void InitObjectPosition();
public:
	World();
	World(LPDIRECT3DDEVICE9);
	~World();
	
	void UpdateObjects(float deltaTime);
	void RenderObjects();

	void SetGrid(Grid* grid);
	Grid* GetGrid();
	void SetTexture(Texture* texture);
	Texture* GetTexture();
};

