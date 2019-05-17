#include "Stage3.h"

Stage3* Stage3::_instance = NULL;

Stage3::Stage3()
{
	Grid::GetInstance()->ReSetGrid(STAGE3_WIDTH, STAGE3_HEIGHT, false);

	this->LoadResource();

	Camera::GetInstance()->setWorldBoundary(STAGE3_WIDTH);

}


Stage3::~Stage3()
{
}

void Stage3::LoadResource()
{
	this->objects->push_back(MainCharacter::GetInstance());

	this->map = new Map(PATH_POS_MAP_3, PATH_TEXTURE_MAP_3, ID_TEXTURE_MAP_3);

	fstream fs(PATH_POS_GROUND_MAP_3);

	int numberOfGround, left, top, right, bottom, canStick;

	fs >> numberOfGround;

	vector<RECT>* bricks = new vector<RECT>();

	for (int i = 0; i < numberOfGround; i++) {
		bricks->clear();
		fs >> left >> top >> right >> bottom >> canStick;

		RECT rect;
		rect.top = top;
		rect.left = left;
		rect.right = right;
		rect.bottom = bottom;

		this->InitStaticObjects(rect, bricks);

		for (int i = 0; i < bricks->size(); i++) {
			RECT rect = bricks->at(i);
			Brick * brick = new Brick(rect.left, rect.top, rect.right, rect.bottom, canStick);
			this->objects->push_back(brick);
		}
	}

	fs.close();
	MainCharacter::GetInstance()->SetPosition(50, 120);

	this->objects->push_back(Boss::GetInstance());

	for (auto obj : *objects) {
		Grid::GetInstance()->Add(obj);
	}
	
	vector<BossBullet*> *bullets = Boss::GetInstance()->GetBullets();

	for (int i = 0; i < bullets->size(); i++) {
		this->objects->push_back(bullets->at(i));
	}

	delete bricks;
}

void Stage3::Update(float deltaTime)
{
	Stage::Update(deltaTime);
}

void Stage3::Render()
{
	Stage::Render();
}
