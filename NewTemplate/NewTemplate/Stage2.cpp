#include "Stage2.h"

Stage2* Stage2::_instance = NULL;

Stage2::Stage2()
{
	Grid::GetInstance()->ReSetGrid(STAGE2_HEIGHT, STAGE2_WIDTH, false);
	MainCharacter::GetInstance()->SetPosition(988, 150);
	this->LoadResource();
	//Camera::GetInstance()->setPosition(D3DXVECTOR2(0, 0));

	Camera::GetInstance()->setWorldBoundary(3072);
}


Stage2::~Stage2()
{
}

void Stage2::LoadResource()
{
	objects->clear();

	this->objects->push_back(MainCharacter::GetInstance());

	this->map = new Map(PATH_POS_MAP_2, PATH_TEXTURE_MAP_2, ID_TEXTURE_MAP_2);

	fstream fs(PATH_POS_GROUND_MAP_2);

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


	//RECT r;
	//r.left = 1088;
	//r.top = 112;
	//r.right = 1103;
	//r.bottom = 207;
	//this->InitBrick(r);

	Ladder* l = new Ladder(1088, 112, 1103, 179);
	this->objects->push_back(l);

	for (int i = 0; i < this->bricks->size(); i++) {
		RECT rect = this->bricks->at(i);
		Brick * brick = new Brick(rect.left, rect.top, rect.right, rect.bottom);
		this->objects->push_back(brick);
	}



	for (int i = 0; i < this->objects->size(); i++) {
		Grid::GetInstance()->Add(this->objects->at(i));
	}
}

void Stage2::Update(float deltaTime)
{
	Stage::Update(deltaTime);
}

void Stage2::Render()
{
	Stage::Render();

}
