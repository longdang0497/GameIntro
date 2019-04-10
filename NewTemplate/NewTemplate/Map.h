#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <fstream>
#include "Sprite.h"
#include "Texture.h"
#include "Define.h"
#include "Game.h"
#include "Camera.h"


class Map
{
private:
	LPDIRECT3DTEXTURE9 texture;
	vector<vector<int>*>* list;
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
	void drawMap();

};

