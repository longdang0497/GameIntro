#pragma once
#include "Grid.h"
#include "DXGraphics.h"
#include "Texture.h"
#include "MainCharacter.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "trace.h"
#include <vector>

// Class này dùng để quản lý các object của thế giới Game
// Bao gồm Map, Sprite, Main, Enemy, Grid, ...

using namespace std; 

class World
{
private:
	Grid* grid;
	LPD3DXSPRITE spriteHandler;
	Texture* texture;
	MainCharacter * gameCharacter;
	vector<D3DXVECTOR2> spriteCoord; // Dùng để lưu lại tọa độ của sprite

	void LoadResources(LPDIRECT3DDEVICE9);
	void InitSprite(LPDIRECT3DDEVICE9);
	void InitObjectPosition();
public:
	World();
	World(LPDIRECT3DDEVICE9);
	~World();
	
	void UpdateObjects(float deltaTime);
	void RenderObjects();

	vector<D3DXVECTOR2> ReadCoord(LPCWSTR filePath, int count);
	//RECT * ReadCurrentSpritePosition();

	void SetGrid(Grid* grid);
	Grid* GetGrid();
	void SetTexture(Texture* texture);
	Texture* GetTexture();
	MainCharacter* GetMainCharacter();
	//LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }
};

