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
	for (int i = 0; i < 200 / 16; i++)
		for (int j = 0; j < 640 / 16 + 1; j++)
		{
			int a = i + camposition.y / 16;
			int b = j + camposition.x / 16;
			left = (list->at(a)->at(b) % numOfColumnTileSet)*16;
			top = (list->at(a)->at(b) / numOfColumnTileSet)*16;
			right = left + 16;
			bottom = top + 16;
			Game::GetInstance()->Draw(j*16 - (int)camposition.x % 16, i*16 - (int)camposition.y % 16, texture, left, top, right, bottom);
		}

	/*for (int i = 0; i < this->list->size(); i++) {
		for (int j = 0; j < this->list->at(i)->size(); j++) {
			int number = this->list->at(i)->at(j);
			Game::GetInstance()->Draw(j*16, i*16, this->texture, number*16, 0, (number+1)*16, 16);
		}
	}*/

}
