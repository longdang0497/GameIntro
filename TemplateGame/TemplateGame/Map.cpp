#include "Map.h"


Map::Map(LPD3DXSPRITE spriteHandler, LPDIRECT3DTEXTURE9 texture, string filePath, int left, int top) {
	/*this->filePath = filePath;

	this->texture = texture;
	if (this->texture == NULL)
		trace(L"Unable to read map texture");
	this->sprite = new Sprite(spriteHandler, this->getTexture(), WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, 1, 1);
	if (this->sprite == NULL)
		trace(L"Unable to load map sprite");
	if (!this->loadMap(this->filePath)) {
		trace(L"Unable to load map");
	}
	this->setLimitation(left, top, m_max_Column * BRICK_SIZE, m_max_Row * BRICK_SIZE);*/
}

Map::Map(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DSURFACE9 screen, DeviceManager * device)
{
	//// Background
	//d3ddv->StretchRect(
	//	screen,		// from 
	//	NULL,				// which portion?
	//	device->GetBackBuffer(),		// to 
	//	NULL,				// which portion?
	//	D3DTEXF_NONE);
	//screen = CreateSurfaceFromFile(device->GetDevice(), BACKGROUND_FILE);
}

Map::~Map() {
	delete sprite;
}

void Map::setLimitation(int x, int y, int width, int height) {
	m_boundary.left = x;
	m_boundary.right = x + width;
	m_boundary.top = y;
	m_boundary.bottom = y + height;
	this->widthLimitation = width;
	this->heightLimitation = height;
}

RECT Map::getBoundary()
{
	return m_boundary;
}

LPDIRECT3DTEXTURE9 Map::getTexture() {
	return this->texture;
}

vector<string> Map::getStringMap() {
	return this->stringMap;
}

bool Map::loadMap(string filePath) {
	ifstream file_txt(filePath);
	string str;
	int row = 0, column = 0;
	while (getline(file_txt, str)) {
		row++;
		if (str.length() > column)
			column = str.length();
		stringMap.push_back(str);
	}

	m_max_Row = row;
	m_max_Column = column;

	if (!stringMap.empty())
		return true;
	return false;
}

void Map::drawMap() {
	for (int i = 0; i < drawBrickArray.size(); i++)
	{
		drawBrick(drawBrickArray[i]);
	}
}

void Map::drawBrick(brick value) {
	//float x_pixel = value.x_pixel;
	//float y_pixel = value.y_pixel;
	//D3DXVECTOR3 pos = D3DXVECTOR3(x_pixel, y_pixel, 0);
	//// draw different type of bricks
	//switch (value.type)
	//{
	//case '1':
	//{
	//	sprite->drawSprite(0, 0, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case '2':
	//{
	//	sprite->drawSprite(0, 1 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case '3':
	//{
	//	sprite->drawSprite(0, 2 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case '4':
	//{
	//	sprite->drawSprite(0, 3 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case '5':
	//{
	//	sprite->drawSprite(0, 4 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case '6':
	//{
	//	sprite->drawSprite(0, 5 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case '7':
	//{
	//	sprite->drawSprite(0, 6 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case '8':
	//{
	//	sprite->drawSprite(0, 7 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case '9':
	//{
	//	sprite->drawSprite(0, 8 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'a':
	//{
	//	sprite->drawSprite(0, 9 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'b':
	//{
	//	sprite->drawSprite(0, 10 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'c':
	//{
	//	sprite->drawSprite(0, 11 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'd':
	//{
	//	sprite->drawSprite(0, 12 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);

	//	break;
	//}
	//case 'e':
	//{
	//	sprite->drawSprite(0, 13 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'f':
	//{
	//	sprite->drawSprite(0, 14 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);

	//	break;
	//}
	//case 'g':
	//{
	//	sprite->drawSprite(0, 15 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'h':
	//{
	//	sprite->drawSprite(0, 16 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'i':
	//{
	//	sprite->drawSprite(0, 17 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'k':
	//{
	//	sprite->drawSprite(0, 18 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'l':
	//{
	//	sprite->drawSprite(0, 19 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'm':
	//{
	//	sprite->drawSprite(0, 20 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'n':
	//{
	//	sprite->drawSprite(0, 21 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'o':
	//{
	//	sprite->drawSprite(0, 22 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'p':
	//{
	//	sprite->drawSprite(0, 23 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'q':
	//{
	//	sprite->drawSprite(0, 24 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'r':
	//{
	//	sprite->drawSprite(0, 25 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 's':
	//{
	//	sprite->drawSprite(0, 26 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 't':
	//{
	//	sprite->drawSprite(0, 27 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'u':
	//{
	//	sprite->drawSprite(0, 28 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'v':
	//{
	//	sprite->drawSprite(0, 29 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'w':
	//{
	//	sprite->drawSprite(0, 30 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'x':
	//{
	//	sprite->drawSprite(0, 31 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'y':
	//{
	//	sprite->drawSprite(0, 32 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'z':
	//{
	//	sprite->drawSprite(0, 33 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'A':
	//{
	//	sprite->drawSprite(0, 34 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'B':
	//{
	//	sprite->drawSprite(0, 35 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'C':
	//{
	//	sprite->drawSprite(0, 36 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'D':
	//{
	//	sprite->drawSprite(0, 37 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'E':
	//{
	//	sprite->drawSprite(0, 38 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'F':
	//{
	//	sprite->drawSprite(0, 39 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'G':
	//{
	//	sprite->drawSprite(0, 40 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'H':
	//{
	//	sprite->drawSprite(0, 41 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'I':
	//{
	//	sprite->drawSprite(0, 42 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'K':
	//{
	//	sprite->drawSprite(0, 43 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'L':
	//{
	//	sprite->drawSprite(0, 44 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'M':
	//{
	//	sprite->drawSprite(0, 45 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'N':
	//{
	//	sprite->drawSprite(0, 46 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'O':
	//{
	//	sprite->drawSprite(0, 47 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'P':
	//{
	//	sprite->drawSprite(0, 48 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'Q':
	//{
	//	sprite->drawSprite(0, 49 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'R':
	//{
	//	sprite->drawSprite(0, 50 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'S':
	//{
	//	sprite->drawSprite(0, 51 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case 'T':
	//{
	//	sprite->drawSprite(0, 52 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case'U':
	//{
	//	sprite->drawSprite(0, 53 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
	//	break;
	//}
	//case '0':
	//{
	//	break;
	//}
	//default:
	//	break;
	//}
}

void Map::Update(int roomID) {

}

void Map::UpdateMap(RECT cameraBound) {
	//drawBrickArray.clear();
	//RECT bound = cameraBound;
	//bound.left -= 2 * BRICK_SIZE;
	//bound.top -= 2 * BRICK_SIZE;
	//vector<string> strBrick = this->getStringMap();

	////may phai kiem tra neu cai brick do nam ben trong cai bound
	//for (int i = 0; i < strBrick.size(); i++)
	//{
	//	for (int j = 0; j < strBrick[i].length(); j++)
	//	{
	//		float x_pixel = m_boundary.left + j * BRICK_SIZE;
	//		float y_pixel = m_boundary.top + i * BRICK_SIZE;
	//		D3DXVECTOR2 point(x_pixel, y_pixel);
	//		if (Math::isPointinRectangle(point, bound)) {
	//			brick new_brick = brick();
	//			new_brick.type = strBrick[i][j];
	//			new_brick.x_pixel = x_pixel;
	//			new_brick.y_pixel = y_pixel;
	//			drawBrickArray.push_back(new_brick);
	//		}
	//	}
	//}
}

int Map::getRow() {
	return this->m_max_Row;
}

int Map::getColumn() {
	return this->m_max_Column;
}


//void Map::inputBrickToGrid(Grid *grid) {
//	if (this->getStringMap().size() <= 0 || grid == nullptr) {
//		return;
//	}
//	for (int i = 0; i < this->stringMap.size(); i++) {
//		for (int j = 0; j < this->stringMap[i].size(); j++) {
//			if (this->stringMap[i][j] != '0'
//				&& this->stringMap[i][j] != 'V'
//				&& this->stringMap[i][j] != 'W'
//				&& this->stringMap[i][j] != 'Z') {
//				float x = (float)j * 32;
//				float y = (float)i * 32;
//				Brick * brick = new Brick(x, y, BRICK_SIZE, BRICK_SIZE);
//				brick->setIndexX(j);
//				brick->setIndexY(i);
//				grid->add(brick);
//			}
//		}
//	}
//}