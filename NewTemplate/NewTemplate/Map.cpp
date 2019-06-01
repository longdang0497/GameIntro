#include "Map.h"



Map::Map()
{
}

Map::Map(LPCWSTR filePath, LPCWSTR tileset, int ID_MAP)
{
	fstream fs(filePath);
	fs >> numOfColumn >> numOfRow >> tileWidth >> tileHeight >> numOfColumnTileSet >> numOfRowTileSet;

	this->list = new vector<vector<int>*>();
	
	for (int i = 0; i < numOfRow; i++) {

		vector<int>* temp = new vector<int>();
		for (int j = 0; j < numOfColumn; j++) {
			int tempNumber;
			fs >> tempNumber;
			temp->push_back(tempNumber);
		}
		this->list->push_back(temp);
	}

	fs.close();

	Texture::GetInstance()->Add(ID_MAP, tileset);
	this->texture = Texture::GetInstance()->Get(ID_MAP);
}


Map::~Map()
{
	//for (int i = 0; i < this->list->size(); i++) {
	//	delete this->list->at(i);
	//}
	//delete this->list;
}

void Map::loadMap(LPCSTR filePath)
{
}

void Map::drawMap()
{
	D3DXVECTOR2 camposition = Camera::GetInstance()->getPosition();

	int top, left, right, bottom;

	for (int i = 0; i < 176 / tileHeight; i++)
		for (int j = 0; j < 240 / tileWidth + 1; j++)
		{
			int a = i + camposition.y / tileWidth;
			int b = j + camposition.x / tileHeight;
			left = (list->at(a)->at(b) % numOfColumnTileSet)*tileWidth;
			top = (list->at(a)->at(b) / numOfColumnTileSet)*tileHeight;
			right = left + tileWidth;
			bottom = top + tileHeight;
			Game::GetInstance()->Draw(j*tileWidth - (int)camposition.x % tileWidth, i*tileHeight - (int)camposition.y % tileHeight + 80, texture, left, top, right, bottom,255);
		}


}