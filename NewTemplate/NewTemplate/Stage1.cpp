#include "Stage1.h"

Stage1* Stage1::_instance = NULL;

Stage1::Stage1()
{
	Grid::GetInstance()->ReSetGrid(STAGE1_HEIGHT, STAGE1_WIDTH, false);
	
	this->LoadResource();

	Camera::GetInstance()->setPosition(D3DXVECTOR2(0, 0));

	Camera::GetInstance()->setWorldBoundary(2048);
}


Stage1::~Stage1()
{
}

void Stage1::LoadResource()
{
	this->objects->push_back(MainCharacter::GetInstance());

	this->map = new Map(PATH_POS_MAP_1, PATH_TEXTURE_MAP_1, ID_TEXTURE_MAP_1);

	fstream fs(PATH_POS_GROUND_MAP_1);

	int numberOfGround, left, top, right, bottom;

	fs >> numberOfGround;

	for (int i = 0; i < numberOfGround; i++) {
		fs >> left >> top >> right >> bottom;

		RECT rect;
		rect.top = top;
		rect.left = left;
		rect.right = right;
		rect.bottom = bottom;

		this->InitBrick(rect);
	}

	fs.close();

	for (int i = 0; i < this->bricks->size(); i++) {
		RECT rect = this->bricks->at(i);
		Brick * brick = new Brick(rect.left, rect.top, rect.right, rect.bottom);
		this->objects->push_back(brick);
	}

	for (int i = 0; i < this->objects->size(); i++) {
		Grid::GetInstance()->Add(this->objects->at(i));
	}
}

void Stage1::Update(float deltaTime)
{
	Stage::Update(deltaTime);
}

void Stage1::Render()
{
	this->map->drawMap();
	Stage::Render();

}
