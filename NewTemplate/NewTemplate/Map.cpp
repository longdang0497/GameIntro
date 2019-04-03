#include "Map.h"



Map::Map()
{
}


Map::~Map()
{
}

Map::Map(LPCWSTR filePath, LPCWSTR tileset, int ID_MAP)
{
	fstream fs(filePath);
	fs >> numOfColumn >> numOfRow >> tileWidth >> tileHeight >> numOfColumnTileSet >> numOfRowTileSet;

	for (int i = 0; i < numOfRow; i++)
		for (int j = 0; j < numOfColumn; j++)
			fs >> list[i][j];


	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_MAP, tileset, SIMON_COLOR);
	texture = textures->Get(ID_MAP);
}

void Map::loadMap(LPCSTR filePath)
{

}

void Map::drawMap(CCamera *cam)
{

	D3DXVECTOR2 camposition = cam->getPosition();

	int top, left, right, bottom;
	for (int i = 0; i < SCREEN_HEIGHT / tileHeight; i++)
		for (int j = 0; j < SCREEN_WIDTH / tileWidth + 1; j++)
		{
			int a = i + camposition.y / tileWidth;
			int b = j + camposition.x / tileHeight;
			left = (list[a][b] % numOfColumnTileSet)*tileWidth;
			top = (list[a][b] / numOfColumnTileSet)*tileHeight;
			right = left + tileWidth;
			bottom = top + tileHeight;
			CGame::GetInstance()->Draw(D3DXVECTOR2(j*tileWidth - (int)camposition.x % tileWidth, i*tileHeight - (int)camposition.y % tileHeight), texture, left, top, right, bottom);
		}

}