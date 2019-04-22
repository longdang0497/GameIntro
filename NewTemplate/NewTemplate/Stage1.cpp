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

	this->InitEnemies(PATH_POS_ENEMIES_MAP_1);
	this->InitItems(PATH_POS_ITEMS_MAP_1);


	for (int i = 0; i < this->objects->size(); i++) {
		Grid::GetInstance()->Add(this->objects->at(i));
	}

	delete bricks;
	MainCharacter::GetInstance()->SetPosition(100, 50);

}

void Stage1::Update(float deltaTime)
{
	Stage::Update(deltaTime);

	//if (numOfJaguar <= 0)
	//{
	//	if (MainCharacter::GetInstance()->GetPosition().x >= 300 && MainCharacter::GetInstance()->GetPosition().x <= 400)
	//	{
	//		Jaguar *a = new Jaguar(D3DXVECTOR3(0, 150, 0), RIGHT);
	//		this->objects->push_back(a);
	//		Grid::GetInstance()->Add(a);
	//	}
	//	else if (MainCharacter::GetInstance()->GetPosition().x >= 1000 && MainCharacter::GetInstance()->GetPosition().x <= 1300)
	//	{
	//		Jaguar *a = new Jaguar(D3DXVECTOR3(1500, 200, 0), LEFT);
	//		this->objects->push_back(a);
	//		Grid::GetInstance()->Add(a);
	//	}
	//}

	//numOfJaguar = 0;
	//for (int i = 0; i < this->objects->size(); i++) {
	//	if (this->objects->at(i)->GetObjectType() == JAGUAR && this->objects->at(i)->GetHP() != 0)
	//		numOfJaguar++;
	//}
}

void Stage1::Render()
{
	Stage::Render();

}
