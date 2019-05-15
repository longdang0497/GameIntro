#include "Stage1.h"

Stage1* Stage1::_instance = NULL;

Stage1::Stage1()
{
	Grid::GetInstance()->ReSetGrid(STAGE1_HEIGHT, STAGE1_WIDTH, false);
	
	this->LoadResource();

	//Camera::GetInstance()->setPosition(D3DXVECTOR2(0, 0));

	Camera::GetInstance()->setWorldBoundary(2048);



	SpecialPoint.push_back(0);
	SpecialPoint.push_back(250);
	SpecialPoint.push_back(1880);
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

	fstream fs2(PATH_POS_HIDE_SATGE_1);

	fs2 >> numberOfGround;
	int type;

	vector<RECT>* hides = new vector<RECT>();
	for (int i = 0; i < numberOfGround; i++) {
		hides->clear();
		fs2 >> type;
		fs2 >> left >> top >> right >> bottom;

		RECT rect;
		rect.top = top;
		rect.left = left;
		rect.right = right;
		rect.bottom = bottom;

		this->InitStaticObjects(rect, hides);

		switch (type)
		{
		case 0:
			for (int i = 0; i < hides->size(); i++) {
				RECT rect = hides->at(i);
				HideObject* brick = new HideObject(rect.left, rect.top, rect.right, rect.bottom, TOP_LADDER);
				this->objects->push_back(brick);
			}
			break;
		case 1:
			for (int i = 0; i < hides->size(); i++) {
				RECT rect = hides->at(i);
				HideObject* brick = new HideObject(rect.left, rect.top, rect.right, rect.bottom, BOTTOM_LADDER);
				this->objects->push_back(brick);
			}
			break;
			case 2:
				for (int i = 0; i < hides->size(); i++) {
					RECT rect = hides->at(i);
					HideObject* brick = new HideObject(rect.left, rect.top, rect.right, rect.bottom, END_MAP);
					this->objects->push_back(brick);
				}
				break;
		default:
			break;
		}
	}

	fs2.close();




	this->InitEnemies(PATH_POS_ENEMIES_MAP_1);

	 //Enemy* e = new Bat({ 100, 100,0 }, 0, 0, 0);
	 //this->objects->push_back(e);


	for (int i = 0; i < this->objects->size(); i++) {
		Grid::GetInstance()->Add(this->objects->at(i));
	}

	delete bricks;
	MainCharacter::GetInstance()->SetPosition(100, 50);



}

void Stage1::Update(float deltaTime)
{
	Stage::Update(deltaTime);

	if (MainCharacter::GetInstance()->GetIsInTheEndOfMap())
		ProcessGame::GetInstance(NULL,0)->SetGameStage(STAGE2);
}

void Stage1::Render()
{
	Stage::Render();

}
