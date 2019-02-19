#pragma once
#include "Grid.h"
#include "DXGraphics.h"

// Class này dùng để quản lý các object của thế giới Game
// Bao gồm Map, Sprite, Main, Enemy, Grid, ...
class World
{
private:
	Grid* grid;
	LPD3DXSPRITE spriteHandler;
	LPDIRECT3DTEXTURE9 texture;

	void LoadResources(LPDIRECT3DDEVICE9);
public:
	World();
	World(LPDIRECT3DDEVICE9);
	~World();
	
	void SetGrid(Grid* grid);
	Grid* GetGrid();
};

