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

	vector<RECT>* bricks = new vector<RECT>();

	for (int i = 0; i < numberOfGround; i++) {
		fs >> left >> top >> right >> bottom;

		RECT rect;
		rect.top = top;
		rect.left = left;
		rect.right = right;
		rect.bottom = bottom;

		this->InitStaticObjects(rect, bricks);

	}

	fs.close();

	for (int i = 0; i < bricks->size(); i++) {
		RECT rect = bricks->at(i);
		Brick * brick = new Brick(rect.left, rect.top, rect.right, rect.bottom);
		this->objects->push_back(brick);
	}

	for (int i = 0; i < this->objects->size(); i++) {
			Grid::GetInstance()->Add(this->objects->at(i));
	}

	//Grid::GetInstance()->Add(MainCharacter::GetInstance());

	delete bricks;

	top = 80;
	left = 0;
	right = 2048;
	bottom = 450;


	Soldier* a = new Soldier(D3DXVECTOR3(300, 100, 0), LEFT);
	objects->push_back(a);
	Grid::GetInstance()->Add(a);
}

void Stage1::Update(float deltaTime)
{
	Stage::Update(deltaTime);

	/*
	if (Camera::GetInstance()->getPosition().x >= 10 && Jaguar::GetInstance()->GetIsActive() == false)
		Jaguar::GetInstance()->SetIsActive(true);
	else if (Camera::GetInstance()->getPosition().x <= 10 && Jaguar::GetInstance()->GetIsActive() == false)
		Jaguar::GetInstance()->SetIsActive(false);*/



	if (350 < MainCharacter::GetInstance()->GetPosition().x && MainCharacter::GetInstance()->GetPosition().x < 450 && numofJaguar < 1)
	{

		Jaguar* a = new Jaguar(D3DXVECTOR3(00, 100, 0), RIGHT);
		objects->push_back(a);
		Grid::GetInstance()->Add(a);
	}

	numofJaguar = 0;

	for (int i = 0; i < this->objects->size(); i++)
	{
		if (objects->at(i)->GetPosition().y >= 350)
		{
			objects->at(i)->SetHP(0);
		}

		if (objects->at(i)->GetObjectType() == JAGUAR && objects->at(i)->GetHP() != 0)
		{
			numofJaguar++;
		}


	}

}

void Stage1::Render()
{
	Stage::Render();

}
