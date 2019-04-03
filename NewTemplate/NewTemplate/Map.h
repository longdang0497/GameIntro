#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <fstream>
#include "Sprites.h"
#include "Textures.h"
#include "Define.h"
#include "Game.h"
#include "Camera.h"

class Map
{
	LPDIRECT3DTEXTURE9 texture;
	int list[250][250];
	int width;
	int height;

	int tileWidth;
	int tileHeight;

	int numOfColumn;
	int numOfRow;

	int numOfColumnTileSet;
	int numOfRowTileSet;

public:
	Map();
	Map(LPCWSTR filePath, LPCWSTR tileset, int ID_MAP);
	~Map();

	void loadMap(LPCSTR filePath);
	void drawMap(CCamera* cam);


};

