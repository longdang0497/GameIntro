#include "Stage1.h"

Stage1* Stage1::_instance = NULL;

Stage1::Stage1()
{
	Grid::GetInstance()->ReSetGrid(STAGE1_HEIGHT, STAGE1_WIDTH, false);
	
	this->LoadResource();

	//Camera::GetInstance()->setPosition(D3DXVECTOR2(0, 0));

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
}

void Stage1::Render()
{
	Stage::Render();
	if (fadeIn)
		FadeInEffect();
	if(fadeOut)
		FadeOutEffect();
}

void Stage1::FadeInEffect()
{
	if (alpha >= 200)
	{
		if (GetTickCount() - TimeToFade > 20)
		{
			Game::GetInstance()->Draw(0, 80, Texture::GetInstance()->Get(ID_TEXTURE_BLACK), 0, 80, 256, 320, alpha);
			TimeToFade = GetTickCount();
			alpha -= 1;
		}
	}
	else
	{
		fadeIn = false;
		TimeToFade = GetTickCount();
	}
}

void Stage1::FadeOutEffect()
{
	if (alpha < 255)
	{
		if (GetTickCount() - TimeToFade > 20)
		{
			Game::GetInstance()->Draw(0, 80, Texture::GetInstance()->Get(ID_TEXTURE_BLACK), 1792, 80, 2048, 300, alpha);
			TimeToFade = GetTickCount();
			alpha += 1;
		}
	}
	else
	{
		fadeOut = false;
		MainCharacter::GetInstance()->SetPosition(50, 120);
		Camera::GetInstance()->setPosition(D3DXVECTOR2(0, 0));
		ProcessGame::GetInstance(NULL, 0)->SetGameStage(STAGE2);
	}
}
